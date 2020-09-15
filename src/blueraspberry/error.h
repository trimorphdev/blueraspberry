#ifndef _ERROR_H
#define _ERROR_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "str_utils/split.h"
#include "str_utils/pad.h"
#include "ansi.h"
#include "lexer_utils/Token.h"

void error(std::string message) {
    //std::cout << ansi::blue("BlueRaspberry", true) << std::endl;
    std::cout << ansi::blue("BlueRaspberry") << " ERROR " << ansi::red(message) << std::endl;

    exit(1);
}

void error(std::string message, std::vector<std::string> stack) {
    std::cout << ansi::blue("BlueRaspberry") << " ERROR: " << ansi::red(message) << std::endl;

    for (int i = 0; i < stack.size(); i++) {
        std::cout << "    at " + ansi::red(stack[i]) << std::endl;
    }

    exit(1);
}

void error(std::string message, std::vector<std::string> stack, std::string str, Token tok) {
    std::cout << ansi::blue("BlueRaspberry") << " ERROR: " << ansi::red(message) << std::endl;

    std::vector<std::string> lines = split(str, '\n');
    std::string line = lines[tok.line - 1];
    std::cout << line << " (Line " + ansi::green(std::to_string(tok.line)) + ")" << std::endl;
    if (tok.value.length() > 1)
        std::cout << padEnd("", tok.character) << ansi::red(padEnd("", tok.value.length(), "~")) << std::endl;
    else
        std::cout << padEnd("", tok.character) << ansi::red(padEnd("", tok.value.length(), "^")) << std::endl;

    for (int i = 0; i < stack.size(); i++) {
        std::cout << "    at " + ansi::red(stack[i]) << std::endl;
    }

    exit(1);
}

#endif