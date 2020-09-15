#include <iostream>
#include <vector>
#include <string>

#include "b1.h"

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

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string path = argv[1];

        std::string module_path = modulePath(path);
        std::string module = loadModule(module_path);

        B1::Context context = B1::Context({
            {"__dirname", constant<B1::String>(new B1::String(dirname(module_path)))},
            #ifdef os
            {"__system", constant<B1::String>(new B1::String(os))}
            #else
            {"__system", constant<B1::String>(new B1::String("other"))}
            #endif
        });

        B1::Script scr = B1::Script(module, context, module_path);
        scr.Run();
    }
    return 0;
}