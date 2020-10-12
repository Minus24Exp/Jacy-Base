#ifndef NATIVEFUNC_H
#define NATIVEFUNC_H

#include <functional>
#include <utility>
#include "object/BaseFunc.h"

using NFArgs = std::map<std::string, obj_ptr>;
using NFBody = std::function<obj_ptr(const NFArgs & args)>;

class NativeFunc : public BaseFunc {
public:
    NativeFunc(ParamList params, NFBody body) : BaseFunc(std::move(params)), body(std::move(body)) {}
    ~NativeFunc() override = default;

    obj_ptr call(Interpreter & ip, const ObjList & args) override;

private:
    NFBody body;
};

std::shared_ptr<NativeFunc> make_nf(ParamList params, NFBody body);

#endif
