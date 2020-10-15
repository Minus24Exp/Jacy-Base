#include "object/BaseFunc.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cFunc = std::make_shared<Class>();

void reg_cFunc(const scope_ptr & global) {
    global->define("Func", Local{VarDeclKind::Val, cFunc});
}