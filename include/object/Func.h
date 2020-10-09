#ifndef FUNC_H
#define FUNC_H

#include "object/Object.h"

class Func;
using func_ptr = std::shared_ptr<Func>;

extern class_ptr cFunc;

class Func : public Object {
public:
    Func() : Object(cFunc) {}
    ~Func() override = default;

private:

};

#endif
