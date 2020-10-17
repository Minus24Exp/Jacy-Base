#ifndef FUNC_H
#define FUNC_H

#include "object/BaseFunc.h"

struct ReturnValue : std::exception {
    explicit ReturnValue(obj_ptr value) : value(value) {}
    obj_ptr value;
};

class Func : public BaseFunc {
public:
    Func(ParamList params, scope_ptr closure, block_ptr body)
        : BaseFunc(std::move(params)), closure(closure), body(std::move(body)) {}
    ~Func() override = default;

    obj_ptr call(const ObjList & args) override;
    func_ptr bind(const obj_ptr & instance) override;

private:
    scope_ptr closure;
    block_ptr body;
};

#endif
