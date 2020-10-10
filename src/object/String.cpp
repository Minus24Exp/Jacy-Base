#include "object/String.h"
#include "object/Class.h"

class_ptr get_cString() {
    static class_ptr cString = std::make_shared<Class>();
    return cString;
}

void reg_cString(const scope_ptr & global) {
    const class_ptr & cString = get_cString();
    global->add("String", Local{VarDeclKind::Val, cString});
}
