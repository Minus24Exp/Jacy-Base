#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cClass = std::make_shared<Class>();

void reg_cClass(const scope_ptr & global) {
    global->define("Class", Local{VarDeclKind::Val, cClass});
}
