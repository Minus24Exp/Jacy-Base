#ifndef STRING_H
#define STRING_H

#include <utility>
#include "object/Object.h"

class String;
using string_ptr = std::shared_ptr<String>;

extern class_ptr cString;

class String : public Object {
public:
    explicit String(std::string value) : Object(cString), value(std::move(value)) {}
    ~String() override = default;

private:
    std::string value;
};

// Constants //
std::map<std::string, string_ptr> string_constants;
static inline string_ptr make_string(const std::string & value) {
    const auto & found = string_constants.find(value);
    if (found != string_constants.end()) {
        return found->second;
    }
    string_constants.emplace(value, std::make_shared<String>(value));
    return string_constants.at(value);
}

#endif
