#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>

class Token {
public:
    std::string name;
    std::string value;
    int line;
    int character;

    Token(std::string name, std::string value, int line, int character) {
        this->name = name;
        this->value = value;
        this->line = line;
        this->character = character;
    }
};

#endif