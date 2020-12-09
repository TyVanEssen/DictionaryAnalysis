#include <iostream>
#include "util.h"

std::string toLower(std::string* input){
    std::string s;
    for (char c : *input){
        if (isalpha(c)){
            s += tolower(c);
        } else {
            s += c;
        }
    }
    *input = s;
    return s;
}