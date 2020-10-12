#ifndef BASEFUNC_H
#define BASEFUNC_H

#include "object/Object.h"
#include "tree/Stmt/Block.h"
#include "object/Callable.h"

class Interpreter;

class BaseFunc;
using func_ptr = std::shared_ptr<BaseFunc>;

class_ptr get_cFunc();
void reg_cFunc(const scope_ptr & global);

struct Param {
    std::string name;
    obj_ptr default_val;
};

using ParamList = std::vector<Param>;

const auto cast_to_f = [](const obj_ptr & obj) { return std::static_pointer_cast<BaseFunc>(obj); };

class BaseFunc : public Object, public Callable {
public:
    ObjType type = ObjType::Func;

    BaseFunc(ParamList params) : Object(get_cFunc()), params(std::move(params)) {}
    ~BaseFunc() override = default;

    size_t required_argc() const override {
        return std::count_if(params.begin(), params.end(), [](const auto & param){
            return !param.default_val;
        });
    }
    size_t argc() const override { return params.size(); }

    virtual obj_ptr call(Interpreter & ip, const ObjList & args) = 0;

    ParamList params;
    scope_ptr closure;
};

#endif
