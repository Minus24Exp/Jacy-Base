#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>
#include "backend/Scope.h"

class String;
class Object;
class Class;

using obj_ptr = std::shared_ptr<Object>;
using ObjList = std::vector<obj_ptr>;

enum class ObjectType {
    Null,
    Object,
    Class,
    Bool,
    Int,
    Float,
    String,
    Func,
    Module,
    List,
    Dict,
    Range
};

extern std::shared_ptr<Class> cObject;

// Try to convert object to str
std::string obj_to_str(obj_ptr obj);

// Try to call hash function
yo_int obj_hash(obj_ptr obj);

class Object : public std::enable_shared_from_this<Object> {
public:
    Object(ObjectType obj_type, std::shared_ptr<Class> _class);
    virtual ~Object() = default;

    ObjectType get_obj_type() const { return obj_type; }

    // All objects except Null and Boolean with value `false` are truthy
    virtual bool truthy() const;

    // Represent object as string
    virtual std::string repr() const;

    bool is(std::shared_ptr<Class> check_class) const;

    void set_fields(const LocalMap & fields);

    bool has(const std::string & name) const;
    obj_ptr get(const std::string & name) const;
    int set(const std::string & name, obj_ptr value);
    
    void define_builtin(const std::string & name, obj_ptr value);
    void define_m_builtin(const std::string & name, obj_ptr value);

protected:
    ObjectType obj_type;
    std::shared_ptr<Class> _class;

    // Instance fields
    LocalMap fields;
};

#endif