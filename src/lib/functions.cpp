#include "lib/functions.h"
#include "object/String.h"
#include "object/BaseFunc.h"

void reg_global_functions(const scope_ptr & global) {
    const auto jc_print = make_nf({{"o"}}, [](const NFArgs & args, obj_ptr instance) -> obj_ptr {
        const auto & to_s = args.at("o")->get("to_s");
        check_type(to_s, ObjType::Func);
        const auto & str = bind_method(args.at("o"), to_s)->call({});
        check_type(str, ObjType::String);
        std::cout << cast_to_s(str)->value << std::endl;
        return nullptr;
    });

    global->define("print", Local{VarDeclKind::Val, jc_print});
}
