#include "interpreter/Interpreter.h"

Interpreter::Interpreter() {
    // Enter global scope
    enter_scope();

    // Register common classes in global scope
    reg_cNull(scope);
    reg_cBool(scope);
    reg_cInt(scope);
    reg_cFloat(scope);
    reg_cString(scope);
    reg_cClass(scope);
    reg_cFunc(scope);
}

void Interpreter::interpret(const StmtList & tree) {
    for (const auto & stmt : tree) {
        stmt->accept(*this);
    }
    exit_scope();
}

// Scope //
void Interpreter::enter_scope() {
    scope = std::make_shared<Scope>(scope);
}

void Interpreter::exit_scope() {
    scope = scope->enclosing;
}

////////////////
// Statements //
////////////////
void Interpreter::visit(ExprStmt * expr_stmt) {
    expr_stmt->expr->accept(*this);
}

void Interpreter::visit(Block * block) {

}

void Interpreter::visit(VarDecl * var_decl) {
    if (scope->has(var_decl->id->get_name())) {
        error(var_decl->id->get_name() + " is already defined", var_decl);
        return;
    }

    value = nullptr;
    if (var_decl->assign_expr) {
        var_decl->assign_expr->accept(*this);
    }
    scope->add(var_decl->id->get_name(), Local{var_decl->kind, value});
}

void Interpreter::visit(FuncDecl * func_decl) {
    const auto & name = func_decl->id->get_name();
    LocalPack funcs = scope->resolve_local(name);
    if (funcs.empty()) {
        error(name + " is not declared in this scope", func_decl->id.get());
    }

    for (const auto & func : funcs) {
        if (func.obj->type != ObjType::Func) {
            error(name + " is already defined in this scope", func_decl->id.get());
            return;
        }

        // TODO: Add type signature
        if (cast_to_f(func.obj)->argc() == func_decl->params.size()) {
            error("Function with same signature is already declared in this scope", func_decl->id.get());
            return;
        }
    }

    ParamList params;
    for (const auto & param : func_decl->params) {
        obj_ptr default_val = nullptr;
        if (param.default_val) {
            param.default_val->accept(*this);
            default_val = value;
        }
        params.push_back(Param{param.id->get_name(), default_val});
    }

    scope->add(name, Local{VarDeclKind::Val, std::make_shared<Func>(params, func_decl->body, scope)});
}

void Interpreter::visit(ReturnStmt * return_stmt) {

}

void Interpreter::visit(WhileStmt * while_stmt) {

}

void Interpreter::visit(ForStmt * for_stmt) {

}

void Interpreter::visit(ClassDecl * class_decl) {

}

void Interpreter::visit(Import * import) {

}

void Interpreter::visit(TypeDecl * type_decl) {

}

/////////////////
// Expressions //
/////////////////
void Interpreter::visit(Literal * literal) {
    switch (literal->token.type) {
        case TokenType::Null: {
            value = NullConst;
        } break;
        case TokenType::Bool: {
            if (literal->token.Bool()) {
                value = TrueConst;
            } else {
                value = FalseConst;
            }
        } break;
        case TokenType::Int: {
            value = make_int(literal->token.Int());
        } break;
        case TokenType::Float: {
            value = make_float(literal->token.Float());
        } break;
        case TokenType::String: {
            value = make_string(literal->token.String());
        } break;
        default: {
            throw DevError("Unexpected type of literal token");
        }
    }
}

// Important: visit(Identifier) gets first found local
// It's not for functions (functions could be overridden)
void Interpreter::visit(Identifier * id) {
    const auto & name = id->get_name();
    const auto & found = scope->locals.find(name);

    if (found->second.empty()) {
        error(name + " is not declared in this scope", id);
        return;
    }

    value = found->second.at(0).obj;

    if (!value) {
        error(name + " is undefined", id);
    }
}

void Interpreter::visit(Infix * infix) {

}

void Interpreter::visit(Prefix * prefix) {

}

void Interpreter::visit(Assign * assign) {
    const auto & name = assign->id->get_name();
    if (!scope->has(name)) {
        error(name + " is not defined", assign->id.get());
    }
    const Local & local = scope->resolve_local(name)[0];
    // If found local is `val` and was assigned
    if (local.kind == VarDeclKind::Val && local.obj) {
        error(name + " is val and cannot be reassigned", assign->id.get());
    }
    assign->value->accept(*this);
    scope->assign(name, value);
}

void Interpreter::visit(SetExpr * set_expr) {

}

void Interpreter::visit(GetExpr * get_expr) {

}

void Interpreter::visit(FuncCall * func_call) {
    enter_scope();
    exit_scope();
}

void Interpreter::visit(IfExpr * if_expr) {

}

void Interpreter::visit(ListExpr * list) {

}

void Interpreter::visit(GetItem * get_item) {

}

void Interpreter::visit(SetItem * set_item) {

}

void Interpreter::visit(DictExpr * dict) {

}

// Errors //
void Interpreter::error(const std::string & msg, Node * node) {
    // TODO: Add current filename
    throw RuntimeException(msg, node->pos, "main");
}