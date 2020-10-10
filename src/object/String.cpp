#include "object/String.h"
#include "object/Class.h"

std::map<std::string, string_ptr> string_constants;
string_ptr make_string(const std::string & value) {
    const auto & found = string_constants.find(value);
    if (found != string_constants.end()) {
        return found->second;
    }
    string_constants.emplace(value, std::make_shared<String>(value));
    return string_constants.at(value);
}

class_ptr get_cString() {
    static class_ptr cString = std::make_shared<Class>();
    return cString;
}

void reg_cString(const scope_ptr & global) {
    const class_ptr & cString = get_cString();
    global->add("String", Local{VarDeclKind::Val, cString});
}
