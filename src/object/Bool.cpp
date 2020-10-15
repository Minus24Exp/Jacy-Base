#include "object/Bool.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

std::shared_ptr<Bool> FalseConst = std::make_shared<Bool>(false);
std::shared_ptr<Bool> TrueConst = std::make_shared<Bool>(true);

class_ptr cBool = std::make_shared<Class>();

void reg_cBool(const scope_ptr & global) {
    global->define("Bool", Local{VarDeclKind::Val, cBool});
}
