#ifndef CLASS_H
#define CLASS_H

#include "interpreter/Scope.h"

extern class_ptr cClass;
void reg_cClass(const scope_ptr & global);

class Class : public Object {
public:
    ObjType type = ObjType::Class;

    Class() : Object(cClass, ObjType::Class) {}
    ~Class() override = default;

    void define(const std::string & name, const Local & field) {
        if (c_fields.find(name) != c_fields.end()) {
            throw JacyException("Unable to redefine "+ name);
        }
        c_fields.emplace(name, field);
    }

    obj_ptr get_field(const std::string & name) const;

    Locals c_fields;
};

#endif
