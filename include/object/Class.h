#ifndef CLASS_H
#define CLASS_H

#include "object/Object.h"

class_ptr get_cClass();
void reg_cClass(const scope_ptr & global);

class Class : public Object {
public:
    Class() : Object(get_cClass()) {}
    ~Class() override = default;

private:
};

#endif
