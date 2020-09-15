#ifndef _HASI_H
#define _HASI_H

#include <vector>

template<class T>
bool has(std::vector<T> v, int i) {
    if (v.size() > i)
        return true;
    
    return false;
};

#endif