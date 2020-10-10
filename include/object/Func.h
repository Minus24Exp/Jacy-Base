#ifndef FUNC_H
#define FUNC_H

#include "object/Object.h"

class Func;
using func_ptr = std::shared_ptr<Func>;

extern class_ptr cFunc;

struct Param {
    std::string name;
    obj_ptr default_val;
};

using ParamList = std::vector<Param>;

const auto cast_to_f = [](const obj_ptr & obj) { return std::static_pointer_cast<Func>(obj); };

class Func : public Object {
public:
    ObjType type = ObjType::Func;

    Func(ParamList params, block_ptr body, scope_ptr closure)
        : Object(cFunc), params(std::move(params)), body(std::move(body)), closure(closure) {}
    ~Func() override = default;

    std::size_t argc() {
        return params.size();
    }

private:
    ParamList params;
    block_ptr body;
    scope_ptr closure;
};

#endif
