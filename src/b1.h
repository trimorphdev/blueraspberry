/* 
BlueRaspberry Programming Language
Copyright (c) 2020 Zack Pace

thanks for using blueraspberry :)
*/

#ifndef _BLUERASPBERRY_H
#define _BLUERASPBERRY_H

#include <string>
#include <vector>
#include <functional>

#include "blueraspberry/blueraspberry.h"
#include "blueraspberry/parser.h"
#include "blueraspberry/lex.h"
#include "blueraspberry/error.h"

BR::Context _IMPORT_DEFAULT(BR::Context cont, std::string str) {
    error("Imports are disabled in this context.");

    return cont;
}

namespace B1 {
    typedef BR::Object Object;
    typedef BR::Null Null;
    typedef BR::Undefined Undefined;
    typedef BR::Bool Bool;
    typedef BR::String String;
    typedef BR::Int Int;
    typedef BR::Float Float;
    typedef BR::VariableReference VariableReference;
    typedef BR::Array Array;
    typedef BR::Function Function;
    typedef BR::Context Context;

    void Error(std::string msg) {
        error(msg);
    }

    void Error(std::string msg, std::vector<std::string> stack) {
        error(msg, stack);
    }

    class Script {
    private:
        std::string code;
        std::string path;
        std::vector<BR::Object*> ast;
        std::vector<std::string> stack;
        BR::Context context;

        std::function<BR::Context(BR::Context, std::string)> _import = _IMPORT_DEFAULT;
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

        BindImport(std::function<BR::Context(BR::Context, std::string)> f) {
            this->_import = f;
        }

        Run() {
            parseAST(this->ast, this->stack, this->code, this->path, this->context, this->_import);
        }
    };
}

#endif