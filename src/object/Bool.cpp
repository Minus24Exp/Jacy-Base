#include "object/Bool.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr get_cBool() {
    static class_ptr cBool = std::make_shared<Class>();
    return cBool;
}

void reg_cBool(const scope_ptr & global) {
    const class_ptr & cBool = get_cBool();
    global->define("Bool", Local{VarDeclKind::Val, cBool});
}
