#ifndef FUNC_H
#define FUNC_H

#include "object/BaseFunc.h"

class Func : public BaseFunc {
public:
    Func(ParamList params, scope_ptr closure, block_ptr body)
        : BaseFunc(std::move(params), closure), body(std::move(body)) {}
    ~Func() override = default;

    obj_ptr call(Interpreter & ip) override;

private:
    block_ptr body;
};

#endif
