#include <iostream>
#include "util.h"

std::string toLower(std::string* input){
    std::string s;
    for (char c : *input){
        s += tolower(c);
    }
    *input = s;
    return s;
}


