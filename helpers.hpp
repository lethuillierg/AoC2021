#ifndef helpers_hpp
#define helpers_hpp

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <regex>

using ll = long long;
using ull = unsigned long long;

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
    
    void show() const {
        std::cout << x << "." << y << std::endl;
    }
    
    bool operator<(const Point& point) const {
        return std::tie(x, y) < std::tie(point.x, point.y);
    }
};

class Matrix {
    std::size_t _size_x, _size_y;
    std::vector<std::vector<int>> _elements;
    
public:
    Matrix(std::size_t size_x, std::size_t size_y) {
        _size_x = size_x;
        _size_y = size_y;
        
        _elements.reserve(size_y);
        
        std::vector<int> rows(size_x, 0);
        
        for(auto y = 0; y < size_y; ++y)
            _elements.emplace_back(rows);
    }
    
    std::size_t getSizeX() const {
        return _size_x;
    }
    
    std::size_t getSizeY() const {
        return _size_y;
    }
    
    void increment(std::size_t x, std::size_t y) {
        ++_elements[y][x];
    }
    
    void incrementAll() {
        for(auto x = 0; x < _size_x; ++x) {
            for(auto y = 0; y < _size_y; ++y) {
                ++_elements[y][x];
            }
        }
    }
    
    void setValue(std::size_t x, std::size_t y, int value) {
        _elements[y][x] = value;
    }
    
    int getValue(std::size_t x, std::size_t y) const {
        return _elements[y][x];
    }
    
    void show() const {
        for(auto y = 0; y < _size_y; ++y) {
            for(auto x = 0; x < _size_x; ++x) {
                std::cout << _elements[y][x] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    void clear() {
        for(auto x = 0; x < _size_x; ++x) {
            for(auto y = 0; y < _size_y; ++y) {
                _elements[y][x] = 0;
            }
        }
    }
    
    // get North, South, East, and West neighbors
    std::vector<std::pair<Point, int>> getFourNeighbors(int x, int y) const {
        std::vector<
            std::pair<Point, int>
        > neighbors;
        
        // north
        if (y > 0)
            neighbors.emplace_back(std::make_pair(Point(x, y - 1), _elements[y - 1][x]));
        
        // right
        if (x < _size_x - 1)
            neighbors.emplace_back(std::make_pair(Point(x + 1, y), _elements[y][x + 1]));

        // left
        if (x > 0)
            neighbors.emplace_back(std::make_pair(Point(x - 1, y), _elements[y][x - 1]));

        // bottom
        if (y < _size_y - 1)
            neighbors.emplace_back(std::make_pair(Point(x, y + 1), _elements[y + 1][x]));
                                   
        return neighbors;
    }
    
    std::vector<std::pair<Point, int>> getAllNeighbors(int x, int y) const {
        std::vector<
            std::pair<Point, int>
        > neighbors;
        
        // north
        if (y > 0)
            neighbors.emplace_back(std::make_pair(Point(x, y - 1), _elements[y - 1][x]));
        
        // north west
        if (y > 0 && x > 0)
            neighbors.emplace_back(std::make_pair(Point(x - 1, y - 1), _elements[y - 1][x - 1]));
        
        // north east
        if (y > 0 && x < _size_x - 1)
            neighbors.emplace_back(std::make_pair(Point(x + 1, y - 1), _elements[y - 1][x + 1]));
        
        // right
        if (x < _size_x - 1)
            neighbors.emplace_back(std::make_pair(Point(x + 1, y), _elements[y][x + 1]));

        // left
        if (x > 0)
            neighbors.emplace_back(std::make_pair(Point(x - 1, y), _elements[y][x - 1]));

        // south
        if (y < _size_y - 1)
            neighbors.emplace_back(std::make_pair(Point(x, y + 1), _elements[y + 1][x]));
        
        // south west
        if (y < _size_y - 1 && x > 0)
            neighbors.emplace_back(std::make_pair(Point(x - 1, y + 1), _elements[y + 1][x - 1]));
        
        // south east
        if (y < _size_y - 1 && x < _size_x - 1)
            neighbors.emplace_back(std::make_pair(Point(x + 1, y + 1), _elements[y + 1][x + 1]));
                                   
        return neighbors;
    }
};

std::vector<Tokens> getInputAsTokens(int fileId = 0, std::string delimiters = " \t");

std::vector<std::vector<int>> permsWithRepetitions(std::size_t length, int default_value, int from_value, int to_value);

unsigned long long sumVector(std::vector<int> const& v);
std::vector<int> getIota(std::size_t length);
std::vector<char> getAlphabet(char* chars, std::size_t size);
unsigned long long n_choose_k(long N, long K);
std::vector<std::string> tokenize(std::string str, std::string delims);
std::vector<ull> tokenizeAsULL(std::string str, std::string delims);


#endif /* helpers_hpp */
