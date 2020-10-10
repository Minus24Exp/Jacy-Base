#ifndef CLASS_H
#define CLASS_H

#include "object/Object.h"

class_ptr get_cClass();

class Class : public Object {
public:
    Class() : Object(get_cClass()) {}
    ~Class() override = default;

private:
};

#endif
