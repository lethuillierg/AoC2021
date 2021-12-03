#include "helpers.hpp"

std::vector<std::string> tokenize(std::string str, std::string delims);

Tokens::Tokens(std::string str, std::string delims) {
    _tokens = tokenize(str, delims);
}

void Tokens::checkPos(int pos) const {
    if (pos >= _tokens.size()) {
        std::cerr << "Error: pos > tokens" << std::endl;
        exit(1);
    }
}

std::string Tokens::to_string(int pos) const {
    checkPos(pos);
    return _tokens.at(pos);
}

long Tokens::to_long(int pos) const {
    checkPos(pos);
    return std::stol(_tokens.at(pos));
}

double Tokens::to_double(int pos) const {
    checkPos(pos);
    return std::stod(_tokens.at(pos));
}
    
void Tokens::show() const {
    for(auto const& token : _tokens)
        std::cout << token << " ";
    std::cout << std::endl;
}

std::vector<std::string> tokenize(std::string str, std::string delimiters) {
    std::vector<std::string> tokens;
    size_t i, j = 0;
    while ((i = str.find_first_not_of(delimiters, j)) != std::string::npos) {
        j = str.find_first_of(delimiters, i + 1);
        tokens.emplace_back(str.substr(i, j - i));
    }
    
    return tokens;
}

std::vector<Tokens> getInputAsTokens(int fileId, std::string delimiters) {
    std::string filepath = "/usr/local/advent/";

    if (fileId <= 0) {
        filepath += "input.txt";
    }
    else {
        filepath += std::to_string(fileId) + ".txt";
    }
    
    std::cout << filepath << std::endl;
    
    std::ifstream infile(filepath);
    
    std::vector<Tokens> v;
    std::string line;
    while (std::getline(infile, line)) {
        Tokens t(line, delimiters);
        v.emplace_back(t);
    }
    
    std::cout << "(" << v.size() << " lines loaded)" << std::endl;
    
    return v;
}
