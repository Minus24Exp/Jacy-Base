#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "tree/BaseVisitor.h"
#include "tree/nodes.h"
#include "Exception.h"
#include "interpreter/Scope.h"
#include "object/objects.h"
#include "lib/functions.h"

class Interpreter : public BaseVisitor {
public:
    static Interpreter & get_instance() {
        static Interpreter instance;
        return instance;
    }

    Interpreter(const Interpreter&) = delete;
    Interpreter(Interpreter&&) = delete;
    Interpreter & operator=(const Interpreter&) = delete;
    Interpreter & operator=(Interpreter&&) = delete;

    void interpret(const StmtList & tree);

private:
    Interpreter();
    ~Interpreter() override = default;

    // Value //
    obj_ptr value;
public:
    obj_ptr get_value() const { return value; }

    // Scope //
    scope_ptr scope;
public:
    scope_ptr get_scope() const { return scope; }
    void enter_scope(scope_ptr nested = nullptr);
    void exit_scope();

    // Statements //
    void visit(ExprStmt * expr_stmt) override;
    void visit(Block * block) override;
    void visit(VarDecl * var_decl) override;
    void visit(FuncDecl * func_decl) override;
    void visit(ReturnStmt * return_stmt) override;
    void visit(WhileStmt * w) override;
    void visit(ForStmt * for_stmt) override;
    void visit(ClassDecl * class_decl) override;
    void visit(Import * import) override;
    void visit(TypeDecl * type_decl) override;

    // Expressions //
    void visit(Literal * literal) override;
    void visit(Identifier * id) override;
    void visit(Infix * infix) override;
    void visit(Prefix * prefix) override;
    void visit(Assign * assign) override;
    void visit(SetExpr * set_expr) override;
    void visit(GetExpr * get_expr) override;
    void visit(FuncCall * func_call) override;
    void visit(IfExpr * if_expr) override;
    void visit(ListExpr * list) override;
    void visit(GetItem * get_item) override;
    void visit(SetItem * set_item) override;
    void visit(DictExpr * dict) override;

    // Errors //
    void error(const std::string & msg, Node * node);
};

#endif
