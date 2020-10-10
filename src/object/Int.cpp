#include "object/Int.h"
#include "object/Class.h"

class_ptr get_cInt() {
    static class_ptr cInt = std::make_shared<Class>();
    return cInt;
}
