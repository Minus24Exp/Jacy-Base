#ifndef VALUE_H
#define VALUE_H

#include <memory>
#include <map>

class Object;
using obj_ptr = std::shared_ptr<Object>;

enum class ObjType {
    Null,
    Bool,
    Int,
    Float,
    String,
    Object,
    Func,
    Class,
};

struct Value {
    ObjType tag;
    obj_ptr obj;
};

#endif
