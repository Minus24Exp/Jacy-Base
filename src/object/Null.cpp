#include "object/Null.h"
#include "object/Class.h"

class_ptr get_cNull() {
    static class_ptr cNull = std::make_shared<Class>();
    return cNull;
}

void reg_cNull(const scope_ptr & global) {
    const class_ptr & cNull = get_cNull();
    global->add("Null", Local{VarDeclKind::Val, cNull});
}