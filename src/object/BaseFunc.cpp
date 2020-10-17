#include "object/BaseFunc.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cFunc = std::make_shared<Class>();

void reg_cFunc(const scope_ptr & global) {
    global->define("Func", Local{VarDeclKind::Val, cFunc});
}

func_ptr bind_method(const obj_ptr & instance, const obj_ptr & method) {
    if (method->type == ObjType::Func) {
        return cast_to_f(method)->bind(instance);
    }
    throw JacyException("Unable to bind non-function object");
}
