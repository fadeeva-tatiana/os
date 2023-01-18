#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace)))
                    .base(),
            s.end());
}

void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

std::string getString(char x) {
    std::string s(1, x);
    return s;
}
