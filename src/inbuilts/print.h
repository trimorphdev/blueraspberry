#ifndef _BR_INB_PRINT_H
#define _BR_INB_PRINT_H

#include <string>

#include "../b1.h"
#include "../blueraspberry/ansi.h"

namespace _PRINT_BACKEND {
    std::string getansi(B1::Object* obj) {
        if (BR::String *item = dynamic_cast<BR::String*>(obj)) {
            return item->value;
        } else if (BR::Null *item = dynamic_cast<BR::Null*>(obj)) {
            return ansi::yellow("null");
        } else if (BR::Undefined *item = dynamic_cast<BR::Undefined*>(obj)) {
            return "undefined";
        } else if (BR::Bool *item = dynamic_cast<BR::Bool*>(obj)) {
            if (item->value == true)
                return ansi::yellow("true");
            else
                return ansi::yellow("false");
        } else if (BR::Int *item = dynamic_cast<BR::Int*>(obj)) {
            return ansi::yellow(std::to_string(item->value));
        } else if (BR::Float *item = dynamic_cast<BR::Float*>(obj)) {
            return ansi::yellow(std::to_string(item->value));
        } else {
            return "[Object object]";
        }
    }

    std::string genstr(B1::Array arr) {
        std::vector<B1::Object*> data = arr.data;
        std::string res = "";

        for (int i = 0; i < data.size(); i++) {
            std::string ires = getansi(data[i]);

            if (res == "") res += ires;
            else res += " " + ires;
        }

        return res;
    }
}

B1::Object* print(B1::Context cont, B1::Array args) {
    std::cout << _PRINT_BACKEND::genstr(args) << std::endl;

    return new B1::Undefined();
}

#endif