#ifndef FLOAT_H
#define FLOAT_H

#include "object/Object.h"

class Float;
using float_ptr = std::shared_ptr<Float>;

extern class_ptr cFloat;
void reg_cFloat(const scope_ptr & global);

class Float : public Object {
public:
    ObjType type = ObjType::Float;

    explicit Float(double value) : Object(cFloat, ObjType::Float), value(value) {}
    ~Float() override = default;

private:
    double value;
};

// Constants //
float_ptr make_float(double value);

#endif
