#include "interpreter/Interpreter.h"

Interpreter::Interpreter() {
    // Enter global scope
    enter_scope();

    // Register common classes in global scope
    reg_cClass(scope);
    reg_cObject(scope);
    reg_cNull(scope);
    reg_cBool(scope);
    reg_cInt(scope);
    reg_cFloat(scope);
    reg_cString(scope);
    reg_cFunc(scope);
    reg_global_functions(scope);
}

void Interpreter::interpret(const StmtList & tree) {
    for (const auto & stmt : tree) {
        stmt->accept(*this);
    }
    exit_scope();
}

// Scope //
void Interpreter::enter_scope(scope_ptr nested) {
    if (nested) {
        scope = nested;
    } else {
        scope = std::make_shared<Scope>(scope);
    }
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
    try {
        scope->define(var_decl->id->get_name(), Local{var_decl->kind, value});
    } catch (JacyException & je) {
        error(je.what(), var_decl);
    }
}

void Interpreter::visit(FuncDecl * func_decl) {
    const auto & name = func_decl->id->get_name();

    ParamList params;
    for (const auto & param : func_decl->params) {
        obj_ptr default_val = nullptr;
        if (param.default_val) {
            param.default_val->accept(*this);
            default_val = value;
        }
        params.push_back(Param{param.id->get_name(), default_val});
    }

    try {
        scope->define(name, Local{VarDeclKind::Val, std::make_shared<Func>(params, scope, func_decl->body)});
    } catch (JacyException & je) {
        error(je.what(), func_decl);
    }
}

void Interpreter::visit(ReturnStmt * return_stmt) {
    return_stmt->expr->accept(*this);
    throw ReturnValue(value);
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
    try {
        value = scope->get(id->get_name());
    } catch (JacyException & je) {
        error(je.what(), id);
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
    assign->value->accept(*this);

    try {
        scope->set(name, value);
    } catch (JacyException & je) {
        error(je.what(), assign);
    }
}

void Interpreter::visit(SetExpr * set_expr) {

}

void Interpreter::visit(GetExpr * get_expr) {
    // Dont forget about function binding
}

void Interpreter::visit(FuncCall * func_call) {
    func_call->left->accept(*this);
    if (value->type != ObjType::Func) {
        error("Expression is not a function", func_call);
    }
    func_ptr func = cast_to_f(value);

    const auto & required_argc = std::count_if(func->params.begin(), func->params.end(), [](const auto & param) {
        return !param.default_val;
    });

    if (func_call->args.size() < required_argc || func_call->args.size() > func->params.size()) {
        error("Unexpected count of arguments (at least "+ std::to_string(required_argc)
            +" expected, maximum: "+ std::to_string(func->params.size()) +")", func_call);
    }

    enter_scope(func->closure);

    ObjList args;
    for (size_t arg_n = 0; arg_n < func->params.size(); arg_n++) {
        const auto & arg = func_call->args[arg_n];
        arg->accept(*this);
        args.push_back(value);
    }

    ArgsCmpResult comparison = func->cmp_args(args);
    if (comparison == ArgsCmpResult::TooFew) {
        error("Too few arguments in function call (minimum "+ std::to_string(func->required_argc()) +" expected)", func_call);
    } else if(comparison == ArgsCmpResult::TooMany) {
        error("Too many arguments in function call (maximum "+ std::to_string(func->argc()) +" expected)", func_call);
    }

    try {
        value = func->call(args);
    } catch (JacyException & je) {
        error(je.what(), func_call);
    }

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