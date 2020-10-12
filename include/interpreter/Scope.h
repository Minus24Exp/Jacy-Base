#ifndef SCOPE_H
#define SCOPE_H

#include <utility>
#include <vector>
#include "Exception.h"
#include "tree/Stmt/VarDecl.h"
#include "object/Object.h"

class Scope;
using scope_ptr = std::shared_ptr<Scope>;

struct Local {
    // Type
    VarDeclKind kind;
    obj_ptr obj;
};

using Locals = std::map<std::string, Local>;

struct Scope {
    explicit Scope(scope_ptr enclosing) : enclosing(std::move(enclosing)) {}
    virtual ~Scope() = default;

    bool has(const std::string & name) {
        const auto & found = locals.find(name);
        return found != locals.end();
    }

    void define(const std::string & name, const Local & local) {
        if (has(name)) {
            throw JacyException(name +" has beed already declared in this scope");
        }
        locals.emplace(name, local);
    }

    void set(const std::string & name, const obj_ptr & value) {
        const auto & found = locals.find(name);
        if (found == locals.end()) {
            if (enclosing) {
                return enclosing->set(name, value);
            } else {
                throw JacyException(name +" is not declared in this scope");
            }
        }
        if (found->second.kind == VarDeclKind::Val && found->second.obj) {
            throw JacyException("Unable to reassign val "+ name);
        }
        locals[name].obj = value;
    }

    obj_ptr get(const std::string & name) {
        const auto & found = locals.find(name);
        if (has(name)) {
            return found->second.obj;
        }
        if (enclosing) {
            return enclosing->get(name);
        }
        throw JacyException(name +" is not declared in this scope");
    }

    scope_ptr enclosing;
    Locals locals;
};

#endif
