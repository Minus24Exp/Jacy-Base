#include "object/Object.h"
#include "object/Class.h"
#include "interpreter/Scope.h"
#include "object/BaseFunc.h"

class_ptr cObject = std::make_shared<Class>();

Object::Object(const class_ptr & _class, ObjType type = ObjType::Object) : _class(_class), type(type) {}

void reg_cObject(const scope_ptr & global) {
    global->define("Object", Local{VarDeclKind::Val, cObject});
}

void check_type(const obj_ptr & obj, const class_ptr & _class) {
    if (!obj->is(_class)) {
        // TODO: Add class name to error and class
        throw JacyException("Invalid type");
    }
}

void check_type(const obj_ptr & obj, ObjType type) {
    if (obj->type != type) {
        throw JacyException("Invalid type");
    }
}

obj_ptr Object::get(const std::string & name) const {
    const auto & found = fields.find(name);
    if (found == fields.end()) {
        return _class->get_field(name);
    }
    return found->second.obj;
}

void Object::set(const std::string & name, const obj_ptr & value) {
    const auto & cf = _class->c_fields.find(name);
    if (cf == _class->c_fields.end()) {
        throw JacyException(name +" is not defined");
    }
    if (cf->second.kind == VarDeclKind::Val) {
        throw JacyException("Unable to redefine val "+ name);
    }
    fields[cf->first].obj = value;
}

bool Object::is(const class_ptr & t) const {
    return _class == t;
}