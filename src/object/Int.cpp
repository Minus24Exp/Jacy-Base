#include "object/Int.h"
#include "object/Class.h"

class_ptr get_cInt() {
    static class_ptr cInt = std::make_shared<Class>();
    return cInt;
}

void reg_cInt(const scope_ptr & global) {
    const class_ptr & cInt = get_cInt();
    global->add("Int", Local{VarDeclKind::Val, cInt});
}
