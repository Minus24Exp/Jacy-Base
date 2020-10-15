#include "object/Null.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cNull = std::make_shared<Class>();

std::shared_ptr<Null> NullConst = std::make_shared<Null>();

void reg_cNull(const scope_ptr & global) {
    global->define("Null", Local{VarDeclKind::Val, cNull});
}