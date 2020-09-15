#ifndef _LEX_H
#define _LEX_H

#include <string>
#include <vector>
#include <regex>
#include <iostream>

#include "lexer.h"
#include "lexer_utils/Token.h"
#include "lexer_utils/RegExp.h"

std::vector<Token> lexer(std::string str) {
    std::vector<RegExp> regexps;
    regexps.push_back(RegExp("string", "^(\".*?\"|'.*?')"));
    regexps.push_back(RegExp("bool", "^(true|false)"));
    regexps.push_back(RegExp("null", "^(null)"));
    regexps.push_back(RegExp("keyword", "^(import|var|const)"));
    regexps.push_back(RegExp("iden", "^([a-zA-Z_][_\\w]*)\\b"));
    regexps.push_back(RegExp("float", "^(\\.\\d+|\\d+\\.\\d+)"));
    regexps.push_back(RegExp("int", "^\\d+"));

    return lex(str, regexps);
}

#endif