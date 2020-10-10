#include "object/Class.h"

class_ptr get_cClass() {
    static class_ptr cClass = std::make_shared<Class>();
    return cClass;
}

void reg_cClass(const scope_ptr & global) {
    const class_ptr & cClass = get_cClass();
    global->add("Class", Local{VarDeclKind::Val, cClass});
}
