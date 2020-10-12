#include "object/Int.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr get_cInt() {
    static class_ptr cInt = std::make_shared<Class>();
    return cInt;
}

void reg_cInt(const scope_ptr & global) {
    const class_ptr & cInt = get_cInt();
    global->define("Int", Local{VarDeclKind::Val, cInt});
}

std::map<long long, int_ptr> int_constants;
int_ptr make_int(long long value)  {
    const auto & found = int_constants.find(value);
    if (found != int_constants.end()) {
        return found->second;
    }
    int_constants.emplace(value, std::make_shared<Int>(value));
    return int_constants.at(value);
}
