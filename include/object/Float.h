#ifndef FLOAT_H
#define FLOAT_H

#include "object/Object.h"

class Float;
using float_ptr = std::shared_ptr<Float>;

class_ptr get_cFloat();
void reg_cFloat(const scope_ptr & global);

class Float : public Object {
public:
    ObjType type = ObjType::Float;

    explicit Float(double value) : Object(get_cFloat()), value(value) {}
    ~Float() override = default;

private:
    double value;
};

// Constants //
extern std::map<double, float_ptr> float_constants;
float_ptr make_float(double value);

#endif
