#include "object/NativeFunc.h"

obj_ptr NativeFunc::call(const std::vector<obj_ptr> & args) {
    NFArgs nf_args;
    for (size_t arg_n = 0; arg_n < params.size(); arg_n++) {
        nf_args[params[arg_n].name] = args[arg_n];
    }
    return body(nf_args, instance);
}

func_ptr NativeFunc::bind(const obj_ptr & instance) {
    return std::make_shared<NativeFunc>(params, body, instance);
}

std::shared_ptr<NativeFunc> make_nf(ParamList params, NFBody body) {
    return std::make_shared<NativeFunc>(std::move(params), std::move(body));
}
