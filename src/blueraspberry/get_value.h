#ifndef _GETVALUE_H
#define _GETVALUE_H

#include <vector>
#include <string>

#include "blueraspberry.h"
#include "lexer_utils/Token.h"
#include "error.h"

struct br_value {
    BR::Object *value;
    int endindex;
};

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
    } else if (toks[i].name == "iden")
        res = new BR::VariableReference(toks[i].value);
    else if (toks[i].value == "\"" || toks[i].value == "'")
        error("Un-terminated string constant, add an ending quote to fix this error.", stack, str, toks[i]);
    else
        error("Invalid value '" + toks[i].value + "'", stack, str, toks[i]);

    br_value result;
    result.value = res;
    result.endindex = endindex;

    return result;
}

#endif