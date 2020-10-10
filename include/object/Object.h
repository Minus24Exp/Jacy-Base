#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include "interpreter/Scope.h"

class Class;
using class_ptr = std::shared_ptr<Class>;

class_ptr get_cObject();

class Object {
public:
    ObjType type = ObjType::Object;

    Object(class_ptr _class = get_cObject()) : _class(_class) {}
    virtual ~Object() = default;

private:
    class_ptr _class;
};

#endif
