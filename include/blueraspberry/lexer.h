#ifndef _LEXER_H
#define _LEXER_H

#include <string>
#include <vector>
#include <regex>

#include "lexer_utils/Token.h"
#include "lexer_utils/RegExp.h"

std::vector<Token> lex(std::string str, std::vector<RegExp> regexps) {
    std::vector<Token> toks = std::vector<Token>();

    /* Defaults */
    regexps.push_back(RegExp("linebreak", "^\\r?\\n"));
    regexps.push_back(RegExp("whitespace", "^\\s"));
    regexps.push_back(RegExp("other", "^[\\s\\S]"));

    int character = 0;
    int line = 1;

    for (size_t c = 0; c < str.size();) {
        for (int i = 0; i < regexps.size(); i++) {
            RegExp regexp = regexps[i];

            std::regex pattern = std::regex(regexp.value);

            std::smatch result;
            std::string sub = str.substr(c, str.length());

            if (std::regex_search(sub, result, pattern)) {
                std::string match = result[0];
                if (regexp.name == "linebreak") {
                    c += match.length();
                    character = 0;
                    line++;
                    break;
                } else if (regexp.name == "whitespace") {
                    c += match.length();
                    character += match.length();
                    break;
                }

                toks.push_back(Token(regexp.name, match, line, character));
                character += match.length();
                c += match.length();
                break;
            }
        }
    }

    return toks;
}

#endif