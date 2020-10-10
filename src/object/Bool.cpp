#include "object/Bool.h"
#include "object/Class.h"

class_ptr get_cBool() {
    static class_ptr cBool = std::make_shared<Class>();
    return cBool;
}