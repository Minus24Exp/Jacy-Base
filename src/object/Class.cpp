#include "object/Class.h"

class_ptr get_cClass() {
    static class_ptr cClass = std::make_shared<Class>();
    return cClass;
}

void register_cClass(scope_ptr global) {

}
