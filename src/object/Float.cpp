#include "object/Float.h"
#include "object/Class.h"

std::map<double, float_ptr> float_constants;
float_ptr make_float(double value) {
    const auto & found = float_constants.find(value);
    if (found != float_constants.end()) {
        return found->second;
    }
    float_constants.emplace(value, std::make_shared<Float>(value));
    return float_constants.at(value);
}

class_ptr get_cFloat() {
    static class_ptr cFloat = std::make_shared<Class>();
    return cFloat;
}

void reg_cFloat(const scope_ptr & global) {
    const class_ptr & cFloat = get_cFloat();
    global->add("Float", Local{VarDeclKind::Val, cFloat});
}
