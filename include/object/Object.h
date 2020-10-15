#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <utility>
#include <vector>
#include <memory>

class Scope;
class Class;
class Object;
using obj_ptr = std::shared_ptr<Object>;
using class_ptr = std::shared_ptr<Class>;
using ObjList = std::vector<obj_ptr>;
using scope_ptr = std::shared_ptr<Scope>;

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

extern class_ptr cObject;
void reg_cObject(const scope_ptr & global);

class Object {
public:
    ObjType type;

    explicit Object(class_ptr _class, ObjType type = ObjType::Object) : _class(std::move(_class)), type(type) {}
    virtual ~Object() = default;

private:
    class_ptr _class;
};

#endif
