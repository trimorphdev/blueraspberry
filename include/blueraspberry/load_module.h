#ifndef _LM_H
#define _LM_H

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sstream>

#include "str_utils/split.h"
#include "error.h"
#include "fs_utils/path.h"
#include "fs_utils/cwd.h"
#include "module_path.h"

inline bool exists (const std::string& name) {
    struct stat buffer;   
    return (stat (name.c_str(), &buffer) == 0); 
}

std::string loadModule(std::string path) {
    if (!exists(path))
        error("Module '" + path + "' doesn't exist.");

    std::string result = "";

    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        if (result != "") result += "\n" + line;
        else result = line;
    }
    file.close();

    return result;
}

#endif