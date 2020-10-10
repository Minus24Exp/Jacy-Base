#ifndef STRING_H
#define STRING_H

#include <utility>
#include "object/Object.h"

class String;
using string_ptr = std::shared_ptr<String>;

class_ptr get_cString();
void reg_cString(const scope_ptr & global);

class String : public Object {
public:
    ObjType type = ObjType::String;

    explicit String(std::string value) : Object(get_cString()), value(std::move(value)) {}
    ~String() override = default;

private:
    std::string value;
};

// Constants //
extern std::map<std::string, string_ptr> string_constants;
string_ptr make_string(const std::string & value);

#endif
