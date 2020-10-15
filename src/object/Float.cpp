#include "object/Float.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cFloat = std::make_shared<Class>();

void reg_cFloat(const scope_ptr & global) {
    global->define("Float", Local{VarDeclKind::Val, cFloat});
}

float_ptr make_float(double value) {
    static std::map<double, float_ptr> float_constants;
    const auto & found = float_constants.find(value);
    if (found != float_constants.end()) {
        return found->second;
    }
    float_constants.emplace(value, std::make_shared<Float>(value));
    return float_constants.at(value);
}
