#ifndef _BR_INB_H
#define _BR_INB_H

#include "b1.h"
#include "inbuilts/print.h"
#include "blueraspberry/fs_utils/path.h"

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

B1::Context add_inbuilts(B1::Context pre, std::string module_path) {
    /* Global Constants */
    pre.set("__dirname", constant<B1::String>(new B1::String(dirname(module_path))));
    pre.set("__filepath", constant<B1::String>(new B1::String(module_path)));

    /* Methods */
    pre.set("print", new B1::Function(print));

    /* System Specific Variables */
    #ifdef os
    pre.set("__system", constant<B1::String>(new B1::String(os)));
    #else
    pre.set("__system", constant<B1::String>(new B1::String("other")));
    #endif

    return pre;
}

#endif