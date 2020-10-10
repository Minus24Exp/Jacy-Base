#ifndef NULL_H
#define NULL_H

#include "object/Object.h"

class_ptr get_cNull();
void reg_cNull(const scope_ptr & global);

class Null : public Object {
public:
    ObjType type = ObjType::Null;

    Null() : Object(get_cNull()) {}
    ~Null() override = default;

private:
};

const std::shared_ptr<Null> NullConst = std::make_shared<Null>();

#endif
