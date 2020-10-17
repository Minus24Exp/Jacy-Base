#include "object/Class.h"

class_ptr cClass = std::make_shared<Class>();

void reg_cClass(const scope_ptr & global) {
    global->define("Class", Local{VarDeclKind::Val, cClass});
}

obj_ptr Class::get_field(const std::string & name) const {
    const auto & found = c_fields.find(name);
    if (found == c_fields.end()) {
        throw JacyException("Field not found "+ name);
    }
    return found->second.obj;
}