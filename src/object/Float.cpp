#include "object/Float.h"
#include "object/Class.h"

class_ptr get_cFloat() {
    static class_ptr cFloat = std::make_shared<Class>();
    return cFloat;
}

void reg_cFloat(const scope_ptr & global) {
    const class_ptr & cFloat = get_cFloat();
    global->add("Float", Local{VarDeclKind::Val, cFloat});
}
