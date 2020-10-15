#ifndef BOOL_H
#define BOOL_H

#include "object/Object.h"

extern class_ptr cBool;
void reg_cBool(const scope_ptr & global);

class Bool : public Object {
public:
    ObjType type = ObjType::Bool;

    explicit Bool(bool value) : Object(cBool, ObjType::Bool), value(value) {}
    ~Bool() override = default;

private:
    bool value;
};

extern std::shared_ptr<Bool> FalseConst;
extern std::shared_ptr<Bool> TrueConst;

#endif
