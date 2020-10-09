#include "interpreter/Interpreter.h"

Interpreter::Interpreter() {}

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

}

void Interpreter::visit(FuncDecl * func_decl) {

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
            value = Value{ObjType::Null, NullConst};
        } break;
        case TokenType::Bool: {
            if (literal->token.Bool()) {
                value = Value{ObjType::Bool, TrueConst};
            } else {
                value = Value{ObjType::Bool, FalseConst};
            }
        } break;
        case TokenType::Int: {
            value = Value{ObjType::Int, make_int(literal->token.Int())};
        } break;
        case TokenType::Float: {
            value = Value{ObjType::Float, make_float(literal->token.Float())};
        } break;
        case TokenType::String: {
            value = Value{ObjType::String, make_string(literal->token.String())};
        } break;
        default: {
            throw DevError("Unexpected type of literal token");
        }
    }
}

// Important: visit(Identifier) gets first found local
// It's not for functions (functions could be overridden)
void Interpreter::visit(Identifier * id) {
    const auto & found = scope->locals.find(id->get_name());

    if (found->second.empty()) {
        error(id->get_name() + " is not defined", id);
        return;
    }

    value = found->second.at(0).val;
}

void Interpreter::visit(Infix * infix) {

}

void Interpreter::visit(Prefix * prefix) {

}

void Interpreter::visit(Assign * assign) {

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