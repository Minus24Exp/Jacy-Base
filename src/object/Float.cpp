#include "object/Float.h"
#include "object/Class.h"

class_ptr get_cFloat() {
    static class_ptr cFloat = std::make_shared<Class>();
    return cFloat;
}