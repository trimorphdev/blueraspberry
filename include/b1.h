/* 
BlueRaspberry Programming Language
Copyright (c) 2020 Zack Pace

thanks for using blueraspberry :)
*/

#ifndef _BLUERASPBERRY_H
#define _BLUERASPBERRY_H

#include <string>
#include <vector>

#include "blueraspberry/blueraspberry.h"
#include "blueraspberry/parser.h"
#include "blueraspberry/lex.h"

namespace B1 {
    typedef BR::Object Object;
    typedef BR::Null Null;
    typedef BR::Undefined Undefined;
    typedef BR::Bool Bool;
    typedef BR::String String;
    typedef BR::Int Int;
    typedef BR::Float Float;
    typedef BR::VariableReference VariableReference;
    typedef BR::Context Context;


    class Script {
    private:
        std::string code;
        std::string path;
        std::vector<BR::Object*> ast;
        std::vector<std::string> stack;
        BR::Context context;
    public:
        Script(std::string code, BR::Context context, std::string path = "@anonymous") {
            this->code = code;
            this->context = context;
            this->path = path;

            std::vector<Token> toks = lexer(code);

            std::vector<std::string> stack = std::vector<std::string>();
            stack.push_back(path);
            this->stack = stack;

            this->ast = parse(toks, code, stack, path);
        }

        Run() {
            parseAST(this->ast, this->stack, this->code, this->path, this->context);
        }
    };
}

#endif