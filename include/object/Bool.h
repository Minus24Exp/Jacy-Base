#ifndef BOOL_H
#define BOOL_H

#include "object/Object.h"

class_ptr get_cBool();

class Bool : public Object {
public:
    ObjType type = ObjType::Bool;

    explicit Bool(bool value) : Object(get_cBool()), value(value) {}
    ~Bool() override = default;

private:
    bool value;
};

const std::shared_ptr<Bool> FalseConst = std::make_shared<Bool>(false);
const std::shared_ptr<Bool> TrueConst = std::make_shared<Bool>(true);

#endif
