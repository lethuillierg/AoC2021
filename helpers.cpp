#include "helpers.hpp"

const int MAZE_FREE = 0;
const int MAZE_WALL = 1;
const int MAZE_PATH = 2;


std::vector<std::string> tokenize(std::string str, std::string delims);

Tokens::Tokens(std::string str, std::string delims) {
    _tokens = tokenize(str, delims);
    _rawLine = str;
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
    std::cout <<_tokens.at(pos) << std::endl;
    return std::stod(_tokens.at(pos));
}
    
void Tokens::show() const {
    for(auto const& token : _tokens)
        std::cout << token << " ";
    std::cout << std::endl;
}

std::vector<std::string> Tokens::regex(std::string pattern) const {
    std::vector<std::string> tokens;
    std::regex rgx = std::regex(pattern);
    std::smatch sm;
    
    std::regex_search(_rawLine, sm, rgx);
        
    if (sm.empty()) {
        std::cerr << "Regex error: input cannot be parsed:" << std::endl;
        std::cerr << _rawLine << std::endl;
        exit(1);
    }
    
    for(auto i = 1; i < sm.size(); ++i)
        tokens.emplace_back(sm[i]);
    
    return tokens;
}

std::string Tokens::getRawLine() const {
    return _rawLine;
}

std::vector<std::string> tokenize(std::string str, std::string delimiters) {
    std::vector<std::string> tokens;
    std::size_t i, j = 0;
    while ((i = str.find_first_not_of(delimiters, j)) != std::string::npos) {
        j = str.find_first_of(delimiters, i + 1);
        tokens.emplace_back(str.substr(i, j - i));
    }
    
    return tokens;
}

std::vector<ull> tokenizeAsULL(std::string str, std::string delimiters) {
    std::vector<ull> tokens;
    std::size_t i, j = 0;
    while ((i = str.find_first_not_of(delimiters, j)) != std::string::npos) {
        j = str.find_first_of(delimiters, i + 1);
        tokens.emplace_back(std::stoull(str.substr(i, j - i)));
    }
    
    return tokens;
}

std::vector<ll> tokenizeAsLL(std::string str, std::string delimiters) {
    std::vector<ll> tokens;
    std::size_t i, j = 0;
    while ((i = str.find_first_not_of(delimiters, j)) != std::string::npos) {
        j = str.find_first_of(delimiters, i + 1);
        tokens.emplace_back(std::stoll(str.substr(i, j - i)));
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

// permutations with repetitions
template<typename InputIt, typename T>
bool nextPermutationWithRepetition(InputIt begin, InputIt end, T fromValue, T toValue) {
    auto it = std::find_if_not(std::make_reverse_iterator(end),
                               std::make_reverse_iterator(begin),
                               [&toValue](auto current) { return toValue == current; });

    if (it == std::make_reverse_iterator(begin))
        return false;

    auto bound_element_iterator = std::prev(it.base());

    (*bound_element_iterator)++;
    std::fill(std::next(bound_element_iterator), end, fromValue);

    return true;
}

std::vector<std::vector<int>> permsWithRepetitions(std::size_t length, int defaultValue, int fromValue, int toValue) {
    std::vector<std::vector<int>> perms;
    std::vector<int> vec(length, defaultValue);

    do {
        perms.emplace_back(vec);
    } while (nextPermutationWithRepetition(vec.begin(), vec.end(), fromValue, toValue));

    return perms;
}

// sum vector
unsigned long long sumVector(std::vector<int> const& v) {
    return std::accumulate(v.begin(), v.end(), 0);
}

// iota
std::vector<int> getIota(std::size_t length) {
    std::vector<int> l(length);
    std::iota(l.begin(), l.end(), 0);
    return l;
}

// alphabet
std::vector<char> getAlphabet(char* chars, std::size_t size) {
    std::vector<char> alphabet(chars, chars + size);
    return alphabet;
}

// n choose k
unsigned long long n_choose_k(long N, long K) {
    unsigned long long result = 1;
    for (int i = 1; i <= K; i++) {
        result *= N - (K - i);
        result /= i;
    }
    return result;
}

bool Solve(Matrix& maze, int x, int y, Point endingPoint, bool silent){
    // Make the move (if it's wrong, we will backtrack later.
    maze.setValue(x, y, MAZE_PATH);
    
    // Check if we have reached our goal.
    if (x == endingPoint.x && y == endingPoint.y)
        return true;

    // Recursively search for our goal.
    if (x > 0 && maze.getValue(x - 1, y) == MAZE_FREE && Solve(maze, x - 1, y, endingPoint, silent))
        return true;
    
    if (x < maze.getSizeX() && maze.getValue(x + 1, y) == MAZE_FREE && Solve(maze, x + 1, y, endingPoint, silent))
        return true;
    
    if (y > 0 && maze.getValue(x, y - 1) == MAZE_FREE && Solve(maze, x, y - 1, endingPoint, silent))
        return true;
    
    if (y < maze.getSizeY() && maze.getValue(x, y + 1) == MAZE_FREE && Solve(maze, x, y + 1, endingPoint, silent))
        return true;

    // Otherwise we need to backtrack and find another solution.
    maze.setValue(x, y, MAZE_FREE);

    // If you want progressive update, uncomment these lines...
    if (!silent) {
        std::cout << "- progress -" << std::endl;
        maze.show();
        std::cout << std::endl;
    }
    return false;
};

std::vector<Point> solveMaze(Matrix& maze, Point const& startingPoint, Point const& endingPoint, bool silent) {
    std::vector<Point> solvingPath;

    if (Solve(maze, startingPoint.x, startingPoint.y, endingPoint, silent)) {
        std::cout << "- SOLUTION -" << std::endl;
        maze.show();
        
        for(auto i = 0; i < maze.getSizeY(); ++i)
            for(auto j = 0; j < maze.getSizeX(); ++j)
                if (maze.getValue(i, j) == 2)
                    solvingPath.emplace_back(Point(i, j));
    }
    else {
        std::cout << "Maze: no solution" << std::endl;
    }
    
    return solvingPath;
}
