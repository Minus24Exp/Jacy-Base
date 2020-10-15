#include "object/String.h"
#include "object/Class.h"
#include "interpreter/Scope.h"

class_ptr cString = std::make_shared<Class>();

void reg_cString(const scope_ptr & global) {
    global->define("String", Local{VarDeclKind::Val, cString});
}

string_ptr make_string(const std::string & value) {
    static std::map<std::string, string_ptr> string_constants;
    const auto & found = string_constants.find(value);
    if (found != string_constants.end()) {
        return found->second;
    }
    string_constants.emplace(value, std::make_shared<String>(value));
    return string_constants.at(value);
}
