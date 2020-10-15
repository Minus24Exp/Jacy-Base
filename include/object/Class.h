#ifndef CLASS_H
#define CLASS_H

#include "object/Object.h"

extern class_ptr cClass;
void reg_cClass(const scope_ptr & global);

class Class : public Object {
public:
    ObjType type = ObjType::Class;

    Class() : Object(cClass, ObjType::Class) {}
    ~Class() override = default;

private:
};

#endif
