#include "object/Object.h"
#include "object/Class.h"

class_ptr get_cObject() {
    static class_ptr cObject = std::make_shared<Class>();
    return cObject;
}