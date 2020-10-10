#ifndef SCOPE_H
#define SCOPE_H

#include <utility>
#include <vector>
#include "tree/Stmt/VarDecl.h"
#include "object/Value.h"

class Scope;
using scope_ptr = std::shared_ptr<Scope>;

struct Local {
    // Type
    VarDeclKind kind;
    obj_ptr obj;
};

using LocalPack = std::vector<Local>;
using Locals = std::map<std::string, LocalPack>;

struct Scope {
    explicit Scope(scope_ptr enclosing) : enclosing(std::move(enclosing)) {}
    virtual ~Scope() = default;

    bool has(const std::string & name) {
        const auto & found = locals.find(name);
        return found != locals.end() && !found->second.empty();
    }

    void add(const std::string & name, const Local & local) {
        locals[name].push_back(local);
    }

    void assign(const std::string & name, const obj_ptr & val) {
        // As far as `val`-kind variables cannot be reassigned, make it `var`
        // It must be handled by Interpreter
        locals[name] = {{VarDeclKind::Var, val}};
    }

    LocalPack resolve_local(const std::string & name) {
        const auto & found = locals.find(name);
        if (found != locals.end()) {
            return found->second;
        }
        if (enclosing) {
            return enclosing->resolve_local(name);
        }
        return {};
    }

    scope_ptr enclosing;
    Locals locals;
};

#endif
