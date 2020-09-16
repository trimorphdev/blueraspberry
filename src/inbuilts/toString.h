#ifndef _BR_INB_TOSTRING_H
#define _BR_INB_TOSTRING_H

#include <string>
#include <vector>

#include "../b1.h"
//#include "../blueraspberry/ansi.h"

B1::Object* toString(B1::Context cont, B1::Array args);

namespace _TOSTRING_BACKEND {
    std::string convertToString(B1::Object *obj);
    std::string arrayToString(B1::Array *arr);

    std::string convertToString(B1::Object *obj) {
        if (BR::String *item = dynamic_cast<BR::String*>(obj)) {
            return item->value;
        } else if (BR::Null *item = dynamic_cast<BR::Null*>(obj)) {
            return "null";
        } else if (BR::Undefined *item = dynamic_cast<BR::Undefined*>(obj)) {
            return "undefined";
        } else if (BR::Bool *item = dynamic_cast<BR::Bool*>(obj)) {
            if (item->value == true)
                return "true";
            else
                return "false";
        } else if (BR::Int *item = dynamic_cast<BR::Int*>(obj)) {
            return std::to_string(item->value);
        } else if (BR::Float *item = dynamic_cast<BR::Float*>(obj)) {
            return std::to_string(item->value);
        } else if (BR::Array *item = dynamic_cast<BR::Array*>(obj)) {
            return arrayToString(item);
        } else
            return "[Object object]";
    }

    std::string arrayToString(B1::Array *arr) {
        std::string str = "";

        for (int i = 0; i < arr->data.size(); i++) {
            std::string value = convertToString(arr->data[i]);
            if (str == "") str = value;
            else str += ", " + value;
        }

        return "[ " + str + " ]";
    }
}

B1::Object* toString(B1::Context cont, B1::Array args) {
    if (args.data.size() == 0)
        B1::Error("toString() expects an argument.");

    B1::Object* obj = args.data[0];
    std::string value = _TOSTRING_BACKEND::convertToString(obj);

    return new B1::String(value);
}

#endif