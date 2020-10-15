#ifndef INT_H
#define INT_H

#include "object/Object.h"

class Int;
using int_ptr = std::shared_ptr<Int>;

extern class_ptr cInt;
void reg_cInt(const scope_ptr & global);

class Int : public Object {
public:
    ObjType type = ObjType::Int;

    explicit Int(long long value) : Object(cInt, ObjType::Int), value(value) {}
    ~Int() override = default;

private:
    long long value;
};

// Constants //
int_ptr make_int(long long value);

#endif
