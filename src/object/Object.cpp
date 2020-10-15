#include "object/Object.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cObject = std::make_shared<Class>();

void reg_cObject(const scope_ptr & global) {
    global->define("Object", Local{VarDeclKind::Val, cObject});
}
