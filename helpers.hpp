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
    std::string _rawLine;
    
public:
    Tokens(std::string str, std::string delims);
    void checkPos(int pos) const;
    std::string to_string(int pos) const;
    long to_long(int pos) const;
    double to_double(int pos) const;
    void show() const;
    std::string getRawLine() const;
};

std::vector<Tokens> getInputAsTokens(int fileId = 0, std::string delimiters = " \t");

std::vector<std::vector<int>> permsWithRepetitions(std::size_t length, int default_value, int from_value, int to_value);

unsigned long long getSum(std::vector<int> const& v);
std::vector<int> getIota(std::size_t length);
std::vector<char> getAlphabet(char* chars, std::size_t size);
unsigned long long n_choose_k(long N, long K);
std::vector<std::string> tokenize(std::string str, std::string delims);
using namespace std;

#endif /* helpers_hpp */
