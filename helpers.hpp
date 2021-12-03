#ifndef helpers_hpp
#define helpers_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

class Tokens {
    std::vector<std::string> _tokens;
    
public:
    Tokens(std::string str, std::string delims);
    void checkPos(int pos) const;
    std::string to_string(int pos) const;
    long to_long(int pos) const;
    double to_double(int pos) const;
    void show() const;
};

std::vector<Tokens> getInputAsTokens(int fileId = 0, std::string delimiters = " \t");

#endif /* helpers_hpp */
