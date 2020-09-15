#ifndef _MP_H
#define _MP_H

#include <string>

#include "fs_utils/path.h"
#include "fs_utils/cwd.h"

std::string modulePath(std::string path, std::string _cwd = cwd()) {
    if (!hasEnding(path, ".br"))
        path += ".br";
    
    path = join(_cwd, path);

    return path;
}

#endif