#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <utility>
#include <vector>
#include <memory>
#include "tree/Stmt/VarDecl.h"

class Scope;
class Class;
class Object;
using obj_ptr = std::shared_ptr<Object>;
using class_ptr = std::shared_ptr<Class>;
using ObjList = std::vector<obj_ptr>;
using scope_ptr = std::shared_ptr<Scope>;

struct Local {
    // Type
    VarDeclKind kind;
    obj_ptr obj;
};

using Locals = std::map<std::string, Local>;

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

void check_type(const obj_ptr & obj, const class_ptr & _class);
void check_type(const obj_ptr & obj, ObjType obj_type);

class Object : public std::enable_shared_from_this<Object> {
public:
    ObjType type;

    explicit Object(const class_ptr & _class, ObjType type);
    virtual ~Object() = default;

    obj_ptr get(const std::string & name) const;
    void set(const std::string & name, const obj_ptr & value);

    bool is(const class_ptr & t) const;
//    obj_ptr as() {}

    class_ptr _class;
private:
    Locals fields;
};

#endif
