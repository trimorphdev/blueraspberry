#ifndef _PADEND_H
#define _PADEND_H

#include <string>

std::string padEnd(std::string subject, int number, std::string padding = " ") {
    std::string repeated = "";

    for (int i = subject.length(); i < number; i++) {
        repeated += padding;
    }

    return subject + repeated;
}

std::string padStart(std::string subject, int number, std::string padding = " ") {
    std::string repeated = "";

    for (int i = subject.length(); i < number; i++) {
        repeated += padding;
    }

    return repeated + subject;
}

#endif