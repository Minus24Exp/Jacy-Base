#include "object/Func.h"
#include "object/Class.h"

class_ptr get_cFunc() {
    static class_ptr cFunc = std::make_shared<Class>();
    return cFunc;
}
