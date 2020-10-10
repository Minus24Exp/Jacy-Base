#ifndef CLASS_H
#define CLASS_H

#include "object/Object.h"

extern class_ptr cClass;

class Class : public Object {
public:
    Class() : Object(cClass) {}
    ~Class() override = default;

private:
};

#endif
