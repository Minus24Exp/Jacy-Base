#include "object/Int.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cInt = std::make_shared<Class>();

void reg_cInt(const scope_ptr & global) {
    global->define("Int", Local{VarDeclKind::Val, cInt});
}

int_ptr make_int(long long value)  {
    static std::map<long long, int_ptr> int_constants;
    const auto & found = int_constants.find(value);
    if (found != int_constants.end()) {
        return found->second;
    }
    int_constants.emplace(value, std::make_shared<Int>(value));
    return int_constants.at(value);
}
