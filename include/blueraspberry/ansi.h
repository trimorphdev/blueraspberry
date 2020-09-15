#ifndef _ANSI_H
#define _ANSI_H

#include <string>

namespace ansi {
    namespace colors {
        int black = 30;
        int red = 31;
        int green = 32;
        int yellow = 33;
        int blue = 34;
        int magenta = 35;
        int cyan = 36;
        int white = 37;
    }
    
    std::string code(int color, bool light = false) {
        return ("\u001b[" + std::to_string(color)) + (light ? ";1m" : "m");
    }

    std::string wrap(int color, std::string str, bool light = false) {
        return code(color, light) + str + code(0, false);
    }

    std::string black(std::string str, bool light = false) {
        return wrap(colors::black, str, light);
    }

    std::string red(std::string str, bool light = false) {
        return wrap(colors::red, str, light);
    }

    std::string green(std::string str, bool light = false) {
        return wrap(colors::green, str, light);
    }

    std::string yellow(std::string str, bool light = false) {
        return wrap(colors::yellow, str, light);
    }

    std::string blue(std::string str, bool light = false) {
        return wrap(colors::blue, str, light);
    }

    std::string magenta(std::string str, bool light = false) {
        return wrap(colors::magenta, str, light);
    }

    std::string cyan(std::string str, bool light = false) {
        return wrap(colors::cyan, str, light);
    }

    std::string white(std::string str, bool light = false) {
        return wrap(colors::white, str, light);
    }
}

#endif