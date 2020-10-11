#ifndef NATIVEFUNC_H
#define NATIVEFUNC_H

#include <functional>
#include "object/BaseFunc.h"

using NFBody = std::function<>;

class NativeFunc : public BaseFunc {
public:
    NativeFunc(ParamList params, scope_ptr closure, const NFBody & body)
        : BaseFunc(std::move(params), std::move(body), closure), body(body) {}
    ~NativeFunc() override = default;


private:
    NFBody body;
};

#endif
