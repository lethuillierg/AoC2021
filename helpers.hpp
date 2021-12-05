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
#include <regex>

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
    std::vector<std::string> regex(std::string pattern) const;
    std::string getRawLine() const;
};

struct Point {
    long x, y;
    
    Point() : x(0), y(0) {}
    Point(long a, long b) : x(a), y(b) {}
};

class Matrix {
    std::size_t _size_x, _size_y;
    std::vector<std::vector<int>> _elements;
    
public:
    Matrix(std::size_t size_x, std::size_t size_y) {
        _size_x = size_x;
        _size_y = size_y;
        
        _elements.reserve(size_y);
        
        std::vector<int> columns(size_y, 0);
        
        for(auto x = 0; x < size_x; ++x)
            _elements.emplace_back(columns);
    }
    
    std::size_t getSizeX() const {
        return _size_x;
    }
    
    std::size_t getSizeY() const {
        return _size_y;
    }
    
    void increment(std::size_t x, std::size_t y) {
        ++_elements[x][y];
    }
    
    void setValue(std::size_t x, std::size_t y, int value) {
        _elements[x][y] = value;
    }
    
    int getValue(std::size_t x, std::size_t y) const {
        return _elements[x][y];
    }
    
    void show() const {
        for(auto x = 0; x < _size_x; ++x) {
            for(auto y = 0; y < _size_y; ++y) {
                std::cout << _elements[x][y] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    void clear() {
        for(auto x = 0; x < _size_x; ++x) {
            for(auto y = 0; y < _size_y; ++y) {
                _elements[x][y] = 0;
            }
        }
    }
};

std::vector<Tokens> getInputAsTokens(int fileId = 0, std::string delimiters = " \t");

std::vector<std::vector<int>> permsWithRepetitions(std::size_t length, int default_value, int from_value, int to_value);

unsigned long long sumVector(std::vector<int> const& v);
std::vector<int> getIota(std::size_t length);
std::vector<char> getAlphabet(char* chars, std::size_t size);
unsigned long long n_choose_k(long N, long K);
std::vector<std::string> tokenize(std::string str, std::string delims);
using namespace std;


#endif /* helpers_hpp */
