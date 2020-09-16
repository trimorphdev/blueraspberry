#ifndef _PATH_H
#define _PATH_H

#include <string>
#include <vector>

#include "../str_utils/split.h"

#ifdef WINDOWS
#define DELIMITER '\\'
#else
#define DELIMITER '/'
#endif

std::string join(std::string p1, std::string p2) {
    std::vector<std::string> segments1 = resplit(p1, "/|\\\\");
    std::vector<std::string> segments2 = resplit(p2, "/|\\\\");

    std::string res = "";

    for (int i = 0; i < segments1.size(); i++) {
        if (i == 0) res += segments1[i];
        else res += DELIMITER + segments1[i];
    }
    for (int i = 0; i < segments2.size(); i++) {
        if (res.length() == 0) res += segments2[i];
        else res += DELIMITER + segments2[i];
    }

    return res;
}

std::string dirname(std::string p1) {
    std::vector<std::string> segments = resplit(p1, "/|\\\\");
    std::string res = "";

    for (int i = 0; i < segments.size(); i++) {
        if (i == 0) res += segments[i];
        else if (i != segments.size() - 1) res += DELIMITER + segments[i];
    }
    
    return res;
}

#endif