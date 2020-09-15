/*
#include <iostream>
#include <vector>
#include <string>

#include "lexer_utils/RegExp.h"
#include "lexer_utils/Token.h"
#include "parser.h"
#include "load_module.h"
#include "module_path.h"
#include "lex.h"

#if defined(_WIN32)
#define os "windows"
#elif defined(__unix)
#define os "unix"
#elif defined(macintosh)
#define os "macos"
#elif defined(__APPLE__)
#define os "macos"
#elif defined(__linux__)
#define os "linux"
#elif defined(__FreeBSD)
#define os "freebsd"
#elif defined(__ANDROID__)
#define os "android"
#endif

template<typename T, typename std::enable_if<std::is_base_of<BR::Object, T>::value>::type* = nullptr>
T* constant(T *obj) {
    obj->constant = true;

    return obj;
}

/*
int main(int argc, char** argv) {
    if (argc > 1) {
        std::string path = argv[1];

        std::string module_path = modulePath(path);
        std::string module = loadModule(module_path);

        std::vector<std::string> stack;

        stack.push_back(module_path);
        std::vector<Token> toks = lexer(module);
        std::vector<BR::Object*> ast = parse(toks, module, stack, module_path);

        BR::Context context = BR::Context({
            {"__dirname", constant<BR::String>(new BR::String(dirname(module_path)))},
            #ifdef os
            {"__system", constant<BR::String>(new BR::String(os))}
            #else
            {"__system", constant<BR::String>(new BR::String("other"))}
            #endif
        });

        parseAST(ast, stack, module, module_path, context);
        stack.pop_back();
    }
    return 0;
}

*/