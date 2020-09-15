#ifndef _REGEXP_H
#define _REGEXP_H

#include <string>

class RegExp {
public:
    std::string name;
    std::string value;

    RegExp(std::string name, std::string value) {
        this->name = name;
        this->value = value;
    }
};

#endif