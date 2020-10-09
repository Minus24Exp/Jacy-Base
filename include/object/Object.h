#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include "object/Value.h"

class Class;
using class_ptr = std::shared_ptr<Class>;

extern class_ptr cObject;

class Object {
public:
    Object(class_ptr _class) : _class(_class) {}
    virtual ~Object() = default;

private:
    class_ptr _class;
};

#endif
