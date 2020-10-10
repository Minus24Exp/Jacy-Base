#ifndef INT_H
#define INT_H

#include "object/Object.h"

class Int;
using int_ptr = std::shared_ptr<Int>;

class_ptr get_cInt();
void reg_cInt(const scope_ptr & global);

class Int : public Object {
public:
    ObjType type = ObjType::Int;

    explicit Int(long long value) : Object(get_cInt()), value(value) {}
    ~Int() override = default;

private:
    long long value;
};

// Constants //
extern std::map<long long, int_ptr> int_constants;
int_ptr make_int(long long value);

#endif
