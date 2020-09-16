#ifndef _PARSER_H
#define _PARSER_H
#define quote(x) #x

#include <vector>
#include <functional>

#include "lexer_utils/Token.h"
#include "blueraspberry.h"
#include "error.h"
#include "has_index.h"
#include "get_value.h"
#include "ansi.h"
#include "str_utils/pad.h"
#include "fs_utils/path.h"
#include "load_module.h"
#include "module_path.h"
#include "lex.h"
#include "handlevalue.h"

std::vector<BR::Object*> parse(std::vector<Token> toks, std::string str, std::vector<std::string> stack, std::string filename) {
    std::vector<BR::Object*> ast;

    for (int i = 0; i < toks.size();) {
        Token tok = toks[i];

        if (tok.value == "import") {
            if (has<Token>(toks, i + 1)) {
                if (toks[i + 1].name == "string") {
                    ast.push_back(new BR::Statements::Import(toks[i + 1].value.substr(1, toks[i + 1].value.length() - 2)));
                    i += 2;

                    if (has<Token>(toks, i) && toks[i].value == ";")
                        i++;
                } else if (toks[i + 1].value == "'" || toks[i + 1].value == "\"")
                    error("Un-terminated string constant, add an ending quote to fix this error.", stack, str, toks[i + 1]);
                else
                    error("Expected module name, got unexpected token '" + toks[i + 1].value + "'", stack, str, toks[i + 1]);
            } else
                error("Expected a module name, got '<EOF>'", stack, str, toks[i]);
        } else if (tok.value == "var" || tok.value == "const") {
            if (has<Token>(toks, i + 1)) {
                if (toks[i + 1].name == "iden") {
                    if (has<Token>(toks, i + 2)) {
                        if (toks[i + 2].value == "=") {
                            if (has<Token>(toks, i + 3)) {
                                br_value res = get_value(toks, i + 3, str, stack);

                                if (tok.value == "const")
                                    res.value->constant = true;

                                ast.push_back(new BR::Statements::VariableDefinition(toks[i + 1].value, res.value));

                                i = res.endindex;
                                if (has<Token>(toks, i) && toks[i].value == ";")
                                    i++;
                            } else
                                error("Expected value for '" + toks[i + 1].value + "', got '<EOF>'", stack, str, toks[i + 2]);
                        } else {
                            ast.push_back(new BR::Statements::VariableDefinition(toks[i + 1].value, new BR::Undefined()));
                            i += 2;
                            if (has<Token>(toks, i) && toks[i].value == ";")
                                i++;
                        }
                    } else {
                        ast.push_back(new BR::Statements::VariableDefinition(toks[i + 1].value, new BR::Undefined()));
                        i += 2;
                        if (has<Token>(toks, i) && toks[i].value == ";")
                            i++;
                    }
                } else
                    error("Expected variable name, got '" + toks[i + 1].value + "'", stack, str, toks[i + 1]);
            } else
                error("Expected variable name, got '<EOF>'", stack, str, toks[i]);
        } else if (tok.name == "iden") {
            if (has<Token>(toks, i + 1)) {
                if (toks[i + 1].value == "=") {
                    if (has<Token>(toks, i + 2)) {
                        br_value res = get_value(toks, i + 2, str, stack);

                        ast.push_back(new BR::Statements::VariableSet(toks[i].value, res.value));

                        i = res.endindex;
                        if (has<Token>(toks, i) && toks[i].value == ";")
                            i++;
                    } else
                        error("Expected value for '" + toks[i + 1].value + "', got '<EOF>'", stack, str, toks[i + 1]);
                } else if (toks[i + 1].value == "(") {
                    if (has<Token>(toks, i + 2)) {
                        pl_result res = parse_list(toks, i + 2, str, ")", stack);

                        ast.push_back(new BR::Statements::FunctionCall(toks[i].value, BR::Array(res.value)));

                        i = res.endindex + 1;

                        if (has<Token>(toks, i) && toks[i].value == ";")
                            i++;
                    } else  
                        error("Expected ')' or argument, got '<EOF>'.", stack, str, toks[i]);
                } else
                    error("Unexpected token '" + tok.value + "'", stack, str, toks[i]);
            } else
                error("Unexpected token '" + tok.value + "'", stack, str, toks[i]);
        } else
            error("Unexpected token '" + tok.value + "'", stack, str, toks[i]);
    }

    return ast;
}

template<typename Base, typename T>
inline bool instanceof(const T) {
   return std::is_base_of<Base, T>::value;
}

BR::Context parseAST(std::vector<BR::Object*> ast, std::vector<std::string> stack, std::string str, std::string filename, BR::Context context, std::function<BR::Context(BR::Context, std::string)> import) {
    BR::Context source_context = context.Clone();
    
    for (int i = 0; i < ast.size(); i++) {
        BR::Object *curr = ast[i];

        if (BR::Statements::VariableDefinition *item = dynamic_cast<BR::Statements::VariableDefinition*>(curr)) {
            if (BR::Undefined *contextItem = dynamic_cast<BR::Undefined*>(context.get(item->varname))) {
                context.set(item->varname, handlevalue(item->value, context, stack));
                std::cout << ansi::green("DEF ") << padEnd(item->varname, 25) + " -> @VAL" << std::endl;
            } else
                error("Variable '" + item->varname + "' is already defined.", stack);
        } else if (BR::Statements::VariableSet *item = dynamic_cast<BR::Statements::VariableSet*>(curr)) {
            if (BR::Undefined *contextItem = dynamic_cast<BR::Undefined*>(context.get(item->varname)))
                error("Tried to set uninitialized variable '" + item->varname + "'", stack);
            else if (context.get(item->varname)->constant)
                error("Attempted to change the value of constant variable '" + item->varname + "'", stack);
            else {
                context.set(item->varname, handlevalue(item->value, context, stack));
                std::cout << ansi::green("DEF ") << padEnd(item->varname, 25) + " -> @VAL" << std::endl;
            }
        } else if (BR::Statements::Import *item = dynamic_cast<BR::Statements::Import*>(curr)) {
            BR::Context modcontext = source_context.Clone();
            modcontext = import(modcontext, item->module);
            context.merge(modcontext);
        } else if (BR::Statements::FunctionCall *item = dynamic_cast<BR::Statements::FunctionCall*>(curr)) {
            handlefcall(item, context, stack);
        }
    }

    return context;
}

#endif