#include "object/Object.h"
#include "object/Class.h"

class_ptr get_cObject() {
    static class_ptr cObject = std::make_shared<Class>();
    return cObject;
}

void reg_cObject(const scope_ptr & global) {
    const class_ptr & cObject = get_cObject();
    global->add("Object", Local{VarDeclKind::Val, cObject});
}
