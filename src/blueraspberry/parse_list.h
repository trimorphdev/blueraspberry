#ifndef _PARSELIST_H
#define _PARSELIST_H

#include <vector>
#include <string>
#include <iostream>

#include "blueraspberry.h"
#include "lexer_utils/Token.h"
#include "error.h"
#include "get_value.h"

struct pl_result {
    std::vector<BR::Object*> value;
    int endindex;
};

pl_result parse_list(std::vector<Token> toks, int index, std::string str, std::string end, std::vector<std::string> stack) {
    std::vector<BR::Object*> res;
    int endindex = index;
    bool ended = false;

    /* What the list parser is expecting, 0 = value, 1 = delimiter (,) */
    int expecting = 0;
    int first = 1; // whether or not the current token is the first token.
    
    for (int i = index; i < toks.size();) {
        endindex = i;
        Token tok = toks[i];

        if (tok.value == ")") {
            if (!first) {
                if (!expecting)
                    error("Expected value, got '" + tok.value + "'", stack, str, tok);
                else {
                    ended = true;
                    break;
                }
            } else {
                ended = true;
                break;
            }
        }

        if (expecting == 0) {
            if (first)
                first = 0;

            expecting = 1;

            br_value value = get_value(toks, i, str, stack);
            res.push_back(value.value);
            i = value.endindex;
        } else if (expecting == 1) {
            expecting = 0;

            if (tok.value != ",")
                error("Expected ',', got '" + tok.value + "'.", stack, str, tok);
            
            i++;
        }
    }

    if (!ended) {
        error("Expected ')', got '<EOF>'", stack, str, toks[endindex]);
    }

    pl_result result;
    result.value = res;
    result.endindex = endindex;

    return result;
}

#endif