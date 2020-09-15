#ifndef _SPLIT_H
#define _SPLIT_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>

std::vector<std::string> split(std::string strToSplit, char delimeter) {
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

std::vector<std::string> resplit(const std::string & s, std::string rgx_str = "\\s+") {
    std::vector<std::string> elems;
    std::regex rgx (rgx_str);
    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (iter != end)  {
        //std::cout << "S43:" << *iter << std::endl;
        elems.push_back(*iter);
        ++iter;
    }

    return elems;
}

bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length())
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    else
        return false;
}

#endif