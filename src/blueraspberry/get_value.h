#ifndef _GETVALUE_H
#define _GETVALUE_H

#include <vector>
#include <string>
#include "blueraspberry.h"
#include "lexer_utils/Token.h"
#include "error.h"
#include "has_index.h"

struct br_value {
    BR::Object *value;
    int endindex;
};

struct pl_result {
    std::vector<BR::Object*> value;
    int endindex;
};

br_value get_value(std::vector<Token> toks, int i, std::string str, std::vector<std::string> stack);
pl_result parse_list(std::vector<Token> toks, int index, std::string str, std::string end, std::vector<std::string> stack);

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

        if (tok.value == end) {
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

br_value get_value(std::vector<Token> toks, int i, std::string str, std::vector<std::string> stack) {
    BR::Object *res;
    int endindex = i + 1;
    
    if (toks[i].name == "string")
        res = new BR::String(toks[i].value.substr(1, toks[i].value.length() - 2));
    else if (toks[i].name == "int")
        res = new BR::Int(std::stoi(toks[i].value));
    else if (toks[i].name == "float")
        res = new BR::Float(std::stof(toks[i].value));
    else if (toks[i].name == "null")
        res = new BR::Null();
    else if (toks[i].name == "bool") {
        if (toks[i].value == "true")
            res = new BR::Bool(true);
        else
            res = new BR::Bool(false);
    } else if (toks[i].name == "iden") {
        if (has<Token>(toks, i + 1)) {
            if (toks[i + 1].value == "(") {
                if (has<Token>(toks, i + 2)) {
                    pl_result list = parse_list(toks, i + 2, str, ")", stack);
                    res = new BR::Statements::FunctionCall(toks[i].value, BR::Array(list.value));
                    endindex = list.endindex + 1;
                } else  
                    error("Expected ')' or argument, got '<EOF>'.", stack, str, toks[i]);
            } else
                res = new BR::VariableReference(toks[i].value);
        } else
            res = new BR::VariableReference(toks[i].value);
    } else if (toks[i].value == "[") {
        pl_result list = parse_list(toks, i + 1, str, "]", stack);
        res = new BR::Array(list.value);
        endindex = list.endindex + 1;
    } else if (toks[i].value == "\"" || toks[i].value == "'")
        error("Un-terminated string constant, add an ending quote to fix this error.", stack, str, toks[i]);
    else
        error("Invalid value '" + toks[i].value + "'", stack, str, toks[i]);

    br_value result;
    result.value = res;
    result.endindex = endindex;

    return result;
}

#endif