#ifndef NATIVEFUNC_H
#define NATIVEFUNC_H

#include <functional>
#include <utility>
#include "object/BaseFunc.h"

using NFArgs = std::map<std::string, obj_ptr>;
using NFBody = std::function<obj_ptr(const NFArgs & args, obj_ptr instance)>;

class NativeFunc : public BaseFunc {
public:
    NativeFunc(ParamList params, NFBody body, obj_ptr instance = nullptr)
        : BaseFunc(std::move(params)), body(std::move(body)), instance(instance) {}
    ~NativeFunc() override = default;

    obj_ptr call(const ObjList & args) override;
    func_ptr bind(const obj_ptr & instance) override;

private:
    NFBody body;
    obj_ptr instance;
};

std::shared_ptr<NativeFunc> make_nf(ParamList params, NFBody body);

#endif
