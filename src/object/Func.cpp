#include "object/Func.h"
#include "object/Class.h"
#include "interpreter/Interpreter.h"

obj_ptr Func::call(Interpreter & ip, const ObjList & args) {
    scope_ptr previous = ip.get_scope();
    ip.enter_scope(std::make_shared<Scope>(closure));

    for (size_t arg_n = 0; arg_n < params.size(); arg_n++) {
        try {
            // The only exception `define` can throw is about redefinition
            // Note: Custom exception message
            closure->define(params[arg_n].name, Local{VarDeclKind::Val, args[arg_n]});
        } catch (JacyException & je) {
            throw JacyException("Parameter duplication: "+ params[arg_n].name);
        }
    }

    // TODO: Add `void`
    obj_ptr value = nullptr;
    try {
        body->accept(ip);
    } catch (ReturnValue & return_value) {
        value = return_value.value;
    }

    // Enter previous scope
    ip.enter_scope(previous);
    return value;
}