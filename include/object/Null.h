#ifndef NULL_H
#define NULL_H

#include "object/Object.h"

extern class_ptr cNull;
void reg_cNull(const scope_ptr & global);

class Null : public Object {
public:
    ObjType type = ObjType::Null;

    Null() : Object(cNull, ObjType::Null) {}
    ~Null() override = default;

private:
};

extern std::shared_ptr<Null> NullConst;

#endif
