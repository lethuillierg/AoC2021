#include "helpers.hpp"
#include "days.hpp"

std::vector<Tokens> lines;

void getInputTokens(unsigned int day) {
    lines = getInputAsTokens(day);
}

void separator(std::string sep) {
    std::cout << std::endl << sep << std::endl;
}

// -------------------- DAY 1 --------------------

void day1() {
    // Common
    std::vector<long> measurements;
    for(auto const& line : lines) {
        measurements.emplace_back(line.to_long(0));
    }
    
    // Part One
    separator("Day 1:A");
    
    auto solution1 = 0;
    
    auto previous = std::numeric_limits<long>::max();
    //              ^ There is no measurement before
    //                the first measurement

    for(auto measurement : measurements) {
        if (measurement > previous) {
            ++solution1;
        }
        
        previous = measurement;
    }
    
    std::cout << solution1 << std::endl;
    
    // Part Two
    separator("Day 1:B");

    auto windowSize = 3;
    auto solution2 = 0;
    previous = std::numeric_limits<long>::max();
    
    for(auto i = 0; i < measurements.size() - windowSize + 1; ++i) {
        auto current = 0;
        for(auto j = i; j < i + windowSize; ++j)
            current += measurements[j];
        
        if (current > previous)
            ++solution2;
        
        previous = current;
    }
    
    std::cout << solution2 << std::endl;
}

// -------------------- DAY 2 --------------------

void day2() {
    // Common
    std::vector<std::pair<std::string, long>> commands;
    for(auto const& line : lines) {
        commands.emplace_back(line.to_string(0), line.to_long(1));
    }
    
    // Part One
    separator("Day 2:A");
    
    auto horizontal = 0, depth1 = 0, depth2 = 0, aim = 0;

    for(auto command : commands) {
        auto value = command.second;
        if (command.first == "forward") {
            horizontal += value;
            depth2 += value * aim;
        }
        else if (command.first == "down") {
            depth1 += value;
            aim += value;
        }
        else if (command.first == "up") {
            depth1 -= value;
            aim -= value;
        }
    }
    
    auto solution1 = horizontal * depth1;

    std::cout << solution1 << std::endl;
    
    // Part Two
    separator("Day 2:B");
    
    auto solution2 = horizontal * depth2;
    std::cout << solution2 << std::endl;
}

// -------------------- DAY 3 --------------------

void day3() {
    // Common
    std::vector<std::string> reports;
    for(auto const& line : lines) {
        reports.emplace_back(line.to_string(0));
    }
    
    auto binToLong = [](std::string str){
        return std::stoi(str, nullptr, 2);
    };
    
    auto bitsLength = reports[0].size();
    
    // Part One
    separator("Day 3:A");
    
    std::vector<int> bitsCount(bitsLength, 0);
    for(auto const& report : reports) {
        for(auto i = 0; i < bitsLength; ++i) {
            if (report[i] == '1') {
                ++bitsCount[i];
            }
        }
    }
    
    std::string gamma = "", epsilon = "";
    
    for(auto const& b : bitsCount) {
        if (reports.size() - b > static_cast<double>(reports.size()) / 2) {
            gamma += "1";
            epsilon += "0";
        }
        else {
            gamma += "0";
            epsilon += "1";
        }
    }
    
    auto solution1 = binToLong(gamma) * binToLong(epsilon);
    std::cout << solution1 << std::endl;

    // Part Two
    separator("Day 3:B");
    
    auto bitSetCount = 0;
    char criterion;
    
    // Oxygen Generator Rating
    auto oxy = reports;
    std::string oxyRating = "";
    
    for(auto i = 0; i < bitsLength; ++i) {
        bitSetCount = 0;
        for(auto const& o : oxy) {
            if (o[i] == '1')
                ++bitSetCount;
        }
        
        if (bitSetCount >= static_cast<double>(oxy.size()) / 2)
            criterion = '1';
        else
            criterion = '0';
                
        for(int j = static_cast<int>(oxy.size() - 1); j >= 0; --j)
            if (oxy[j][i] != criterion)
                oxy.erase(oxy.begin() + j);

        if (oxy.size() == 1) {
            oxyRating = oxy[0];
            break;
        }
    }
    
    // CO2 Scrubber Rating
    auto co2 = reports;
    std::string co2Rating = "";
    bitSetCount = 0;
    
    for(auto i = 0; i < bitsLength; ++i) {
        bitSetCount = 0;
        for(auto const& o : co2) {
            if (o[i] == '1')
                ++bitSetCount;
        }
        
        if (bitSetCount < static_cast<double>(co2.size()) / 2)
            criterion = '1';
        else
            criterion = '0';
                
        for(int j = static_cast<int>(co2.size() - 1); j >= 0; --j) {
            if (co2[j][i] != criterion)
                co2.erase(co2.begin() + j);
        }

        if (co2.size() == 1) {
            co2Rating = co2[0];
            break;
        }
    }

    auto solution2 = binToLong(oxyRating) * binToLong(co2Rating);
    std::cout << solution2 << std::endl;
}

// -------------------- DAY 4 --------------------

void day4() {
    // Common
    const auto markedValue = -1; // semaphore
    
    auto showBoard = [](std::vector<std::vector<long>> const& b) {
        for(auto i = 0; i < b.size(); ++i) {
            for(auto j = 0; j < b[i].size(); ++j) {
                std::cout << b[i][j] << " ";
            }
            std::cout << std::endl;
        }
    };
    
    auto wins = [&](std::vector<std::vector<long>> const& board) {
        unsigned int x, y;
        for(auto i = 0; i < 5; ++i) {
            x = 0; y = 0;
            for(auto j = 0; j < 5; ++j) {
                if (board[i][j] == markedValue)
                    ++x;
                
                if (board[j][i] == markedValue)
                    ++y;
            }
            
            if (x == 5 || y == 5) {
                //std::cout << "Winning board" << std::endl;
                //showBoard(board);
                //std::cout << std::endl;
                
                return true;
            }
        }
        return false;
    };
    
    auto markBoard = [](std::vector<std::vector<long>>& board, long calledNumber) {
        for(auto& rows : board)
            for(auto& n : rows)
                if (n == calledNumber)
                    n = -1;
    };
    
    auto sumUmarked = [](std::vector<std::vector<long>> const& board) {
        long acc = 0;
        
        for(auto& rows : board)
            for(auto& n : rows)
                if (n != markedValue)
                    acc += n;
        
        return acc;
    };
    
    std::vector<int> pickedNumbers;
    std::map<int, std::vector<std::vector<long>>> boards;
    
    int i = 0, j = 0;
    for(auto const& line : lines) {
        auto l = line.getRawLine();
        
        // called numbers
        if (i == 0) {
            for(auto n : tokenize(l, ","))
                pickedNumbers.emplace_back(std::stoi(n));
        }
        
        else if (l == "")
            continue;
        
        // get boards
        else {
                std::vector<long> boardRow {
                    line.to_long(0),
                    line.to_long(1),
                    line.to_long(2),
                    line.to_long(3),
                    line.to_long(4),

                };

                boards[j].emplace_back(boardRow);
            
                if (i % 5 == 0)
                    ++j;
            }
        
        ++i;
    }
    
    auto winningNumber = 0;
    auto winningSum = 0L;
    
    separator("Day 4:A");

    // identify winner
    for(auto n : pickedNumbers) {
        if (winningSum > 0) break;

        for(auto& b : boards) {
            auto& board = b.second;
            markBoard(board, n);
            
            if (wins(board)) {
                winningNumber = n;
                winningSum = sumUmarked(board);
            }
        }
    }
    
    std::cout << winningNumber * winningSum << std::endl;
    
    // Part Two
    separator("Day 4:B");
    
    std::vector<int> winningBoards;
    winningNumber = 0;
    winningSum = 0L;

    for(auto n : pickedNumbers) {
        if (winningSum > 0) break;
        
        // mark
        for(auto& b : boards) {
            auto& boardId = b.first;
            auto& board = b.second;
            
            markBoard(board, n);
            
            if (wins(board) && winningSum == 0) {
                if (std::find(winningBoards.begin(), winningBoards.end(), boardId)
                    == winningBoards.end()
                    ) {
                    winningBoards.emplace_back(boardId);
                }
                
                // all boards are winners:
                if (winningBoards.size() == boards.size()) {
                    winningNumber = n;
                    auto& lastWinningBoard = boards[winningBoards.back()];
                    winningSum = sumUmarked(lastWinningBoard);
                }
            }
        }
    }
    
    std::cout << winningNumber * winningSum << std::endl;
}

// -------------------- DAY 5 --------------------

void day5() {
    // common
    class Path {
        Point _A, _B;
        
    public:
        Path(Point A, Point B) {
            _A = A;
            _B = B;
            
            // ensure that point A.x <= point B.x
            if (_A.x > _B.x || (_A.x == _B.x && _A.y > _B.y)) {
                std::swap(_A, _B);
            }
        }
        
        Point getPointA() const {
            return _A;
        }
        
        Point getPointB() const {
            return _B;
        }
        
        bool isDiagonal() const {
            return _A.x != _B.x && _A.y != _B.y;
        }
        
        std::vector<Point> getPath() const {
            std::vector<Point> path;
            std::vector<long> xs, ys;
            
            auto topToBottom = (_A.y <= _B.y) ? true : false;
            
            // vertical
            if (_A.y == _B.y) {
                for(auto x = _A.x; x <= _B.x; ++x) {
                    xs.emplace_back(x);
                    ys.emplace_back(_A.y);
                }
            }
            // horizontal
            else if (_A.x == _B.x) {
                if (topToBottom)
                    for(auto y = _A.y; y <= _B.y; ++y) {
                        xs.emplace_back(_A.x);
                        ys.emplace_back(y);
                    }
                else
                    for(auto y = _A.y; y >= _B.y; --y) {
                        xs.emplace_back(_A.x);
                        ys.emplace_back(y);
                    }
            }
            // diagonal
            else {
                for(auto x = _A.x; x <= _B.x; ++x)
                    xs.emplace_back(x);
                
                if (topToBottom)
                    for(auto y = _A.y; y <= _B.y; ++y)
                        ys.emplace_back(y);
                else
                    for(auto y = _A.y; y >= _B.y; --y)
                        ys.emplace_back(y);
            }
                        
            for(auto i = 0; i < xs.size(); ++i)
                path.emplace_back(Point(xs[i], ys[i]));
            
            return path;
        }
    };
    
    std::vector<Path> paths;
    for(auto const& line : lines) {
        auto l = line.regex("(\\d+),(\\d+) -> (\\d+),(\\d+)");
        
        Point A(std::stol(l.at(0)), std::stol(l.at(1)));
        Point B(std::stol(l.at(2)), std::stol(l.at(3)));
        
        paths.emplace_back(A, B);
    }
    
    // get matrix size
    auto max_x = 0L, max_y = 0L;
    for(auto const& path : paths) {
        auto x = std::max(path.getPointA().x, path.getPointB().x);
        auto y = std::max(path.getPointA().y, path.getPointB().y);
        if (x > max_x) max_x = x;
        if (y > max_y) max_y = y;
    }
    
    max_x += 1;
    max_y += 1;
    
    Matrix matrix(max_x, max_y);
    
    // Part One
    separator("Day 5:A");
    
    for(auto const& path : paths) {
        if (!path.isDiagonal()) {
            for(auto const& point : path.getPath()) {
                matrix.increment(point.x, point.y);
            }
        }
    }
        
    auto overlaps = 0;
    
    for(auto x = 0; x < matrix.getSizeX(); ++x)
        for(auto y = 0; y < matrix.getSizeY(); ++y) {
            if (matrix.getValue(x, y) > 1)
                ++overlaps;
        }
    
    std::cout << overlaps << std::endl;
    
    // Part Two
    separator("Day 5:B");
    
    matrix.clear();
    
    for(auto const& path : paths) {
        for(auto const& point : path.getPath()) {
            matrix.increment(point.x, point.y);
        }
    }
    
    overlaps = 0;
    
    for(auto x = 0; x < matrix.getSizeX(); ++x)
        for(auto y = 0; y < matrix.getSizeY(); ++y)
            if (matrix.getValue(x, y) > 1)
                ++overlaps;
    
    std::cout << overlaps << std::endl;
}

// -------------------- DAY 6 --------------------

void day6() {
    std::vector<std::string> timers;
    for(auto const& line : lines) {
        auto l = line.getRawLine();
        timers = tokenize(l, ",");
    }
    
    // Part One
    separator("Day 6:A");
    
    // Naive and unoptimized solution that only
    // works for a small number of days:
    // count the fishes
    
    class Lanternfish {
        int _timer;
        
    public:
        Lanternfish(std::string state) {
            _timer = std::stoi(state);
        }
        
        void newDay() {
            --_timer;
            
            if (_timer < 0) {
                _timer = 6;
            }
        }
        
        int getTimer() const {
            return _timer;
        }
    };
    
    std::vector<Lanternfish> ls;
    for(auto timer : timers)
        ls.emplace_back(Lanternfish(timer));
    
    ull newFishes = 0;
    for(auto day = 0; day < 80; ++day) {
        newFishes = 0;
        for(auto& l : ls) {
            if (l.getTimer() == 0) {
                ++newFishes;
            }
            l.newDay();
        }
        
        for(auto i = 0; i < newFishes; ++i) {
            Lanternfish l("8");
            ls.emplace_back(l);
        }
    }
    
    std::cout << ls.size() << std::endl;
    
    // Part Two
    separator("Day 6:B");
    
    // More optimized approach:
    // count the timers
    
    std::map<int, ull> fishes;
    
    for(auto timer : timers)
        ++fishes[std::stoi(timer)];
        
    for(auto day = 0; day < 256; ++day) {
        newFishes = fishes[0];
        
        // new day: rotation
        // 8s -> 7s, 7s -> 6s, etc.
        for(auto i = 0; i < 8; ++i)
            fishes[i] = fishes[i + 1];
        
        // 6: existing lanterfishes + the ones they generated
        fishes[6] += newFishes;
        
        // 8: new lanternfishes
        fishes[8] = newFishes;
    }
    
    ull total = 0;
    for(auto f : fishes)
        total += f.second;
    
    std::cout << total << std::endl;
}

// -------------------- DAY 7 --------------------
void day7() {
    std::vector<ull> pos;
    for(auto const& line : lines) {
        auto l = line.getRawLine();
        pos = tokenizeAsULL(l, ",");
    }
    
    ull totalFuel1, totalFuel2;
    ull min1 = std::numeric_limits<ull>::max(), min2 = min1;
    
    for(auto alignPos = 0; alignPos < pos.size(); ++alignPos) {
        totalFuel1 = 0; totalFuel2 = 0;
        
        for(auto i = 0; i < pos.size(); ++i) {
            ull steps = llabs(alignPos - (long long)pos[i]);
            totalFuel1 += steps;
            
            for(auto fuel = 1; fuel <= steps; ++fuel)
                totalFuel2 += fuel;
        }
        
        if (totalFuel1 < min1)
            min1 = totalFuel1;

        if (totalFuel2 < min2)
            min2 = totalFuel2;
    }
    
    // Part One
    separator("Day 7:A");
    
    std::cout << min1 << std::endl;
    
    // Part One
    separator("Day 7:B");
    
    std::cout << min2 << std::endl;
}

// -------------------- CURRENT DAY --------------------

void today() {
    for(auto const& line : lines) {
        // auto l = line.to_long(0);
        // auto l = line.getRawLine();
        // auto x = tokenizeAsULL(l, ",");
    }
    
    // Part One
    separator("Day 8:A");
    
    // Part Two
    separator("Day 8:A");
}

void solve(unsigned int day) {
    getInputTokens(day);
    
    switch(day) {
        case 0:
            today(); // CURRENT DAY
            break;
        case 1:
            day1();
            break;
        case 2:
            day2();
            break;
        case 3:
            day3();
            break;
        case 4:
            day4();
            break;
        case 5:
            day5();
            break;
        case 6:
            day6();
            break;
        case 7:
            day7();
            break;
        case 8:
            day8();
            break;
        default:
            std::cerr << "Day not implemented (" << std::to_string(day) << ")" << std::endl;
    }
}
