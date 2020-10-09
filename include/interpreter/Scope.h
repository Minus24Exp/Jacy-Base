#ifndef SCOPE_H
#define SCOPE_H

#include <utility>

#include "object/Value.h"

class Scope;
using scope_ptr = std::shared_ptr<Scope>;

struct Local {
    // Type
    VarDeclKind kind;
    Value val;
};

using LocalPack = std::vector<Local>;
using Locals = std::map<std::string, LocalPack>;

struct Scope {
    explicit Scope(scope_ptr enclosing) : enclosing(std::move(enclosing)) {}
    virtual ~Scope() = default;

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
