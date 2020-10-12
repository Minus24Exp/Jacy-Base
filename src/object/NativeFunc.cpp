#include "object/NativeFunc.h"

obj_ptr NativeFunc::call(Interpreter & ip, const std::vector<obj_ptr> & args) {
    NFArgs nf_args;
    for (size_t arg_n = 0; arg_n < params.size(); arg_n++) {
        nf_args[params[arg_n].name] = args[arg_n];
    }
    return body(nf_args);
}

std::shared_ptr<NativeFunc> make_nf(ParamList params, NFBody body) {
    return std::make_shared<NativeFunc>(std::move(params), std::move(body));
}
