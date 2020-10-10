#include "object/Func.h"
#include "object/Class.h"

class_ptr get_cFunc() {
    static class_ptr cFunc = std::make_shared<Class>();
    return cFunc;
}

void reg_cFunc(const scope_ptr & global) {
    const class_ptr & cFunc = get_cFunc();
    global->add("Func", Local{VarDeclKind::Val, cFunc});
}
