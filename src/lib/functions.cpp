#include "lib/functions.h"

void reg_global_functions(const scope_ptr & global) {
    const auto jc_print = make_nf({{"o"}}, [](const NFArgs & args) -> obj_ptr {
        std::cout << "PRINT" << std::endl;
        return nullptr;
    });

    global->define("print", Local{VarDeclKind::Val, jc_print});
}