#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <utility>
#include "interpreter/Scope.h"

class Class;
using class_ptr = std::shared_ptr<Class>;

class_ptr get_cObject();
void reg_cObject(const scope_ptr & global);

class Object {
public:
    ObjType type = ObjType::Object;

    explicit Object(class_ptr _class = get_cObject()) : _class(std::move(_class)) {}
    virtual ~Object() = default;

private:
    class_ptr _class;
};

#endif
