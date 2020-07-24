#ifndef LOCAL_H
#define LOCAL_H

#include <memory>

class Object;
using obj_ptr = std::shared_ptr<Object>;

class Local;
using LocalMap = std::unordered_map<std::string, Local>;

/**
 * Var - mutable
 * Val - immutable
 * Builtin - immutable built-in
 * MutBuiltin - mutable built-in (it can be only with other Builtin or MutBuiltin, not with Var/Val)
 */
enum class LocalDeclType {
    Var,
    Val,
    Builtin,
    MutBuiltin
};

class Local {
public:
    Local(LocalDeclType decl_type, obj_ptr val) : decl_type(decl_type), val(val) {}
    virtual ~Local() = default;

    LocalDeclType decl_type;
    obj_ptr val;
};

#endif