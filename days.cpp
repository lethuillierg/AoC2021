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

// -------------------- DAY 8 --------------------

void day8() {
    std::vector<
        std::pair<
            std::vector<std::string>, std::vector<std::string>
        >
    > randomizedSegments;
    
    for(auto const& line : lines) {
        auto allDisplays = tokenize(line.getRawLine(), "|");
        auto L = tokenize(allDisplays[0], " ");
        auto R = tokenize(allDisplays[1], " ");
        randomizedSegments.emplace_back(std::make_pair(L, R));
    }
    
    std::map<std::string, int> segmentsType;
    
    segmentsType["abcefg"]    = 0;
    segmentsType["cf"]        = 1;
    segmentsType["acdeg"]     = 2;
    segmentsType["acdfg"]     = 3;
    segmentsType["bcdf"]      = 4;
    segmentsType["abdfg"]     = 5;
    segmentsType["abdefg"]    = 6;
    segmentsType["acf"]       = 7;
    segmentsType["abcdefg"]   = 8;
    segmentsType["abcdfg"]    = 9;

    // Part One
    separator("Day 8:A");
    
    auto total1 = 0;

    for(auto const& rs : randomizedSegments) {
        for(auto const& segmentR : rs.second) {
            auto size = segmentR.size();
            
            // identify numbers by counting the segments
            if (size == 2 || size == 4 || size == 3 || size == 7)
                ++total1;
        }
    }
    
    std::cout << total1 << std::endl;

    // Part Two
    separator("Day 8:B");
    
    // first, sort the segments types
    for(auto& rs : randomizedSegments) {
        for(auto& segmentL : rs.first)
            std::sort(std::begin(segmentL), std::end(segmentL));
        
        for(auto& segmentR : rs.second)
            std::sort(std::begin(segmentR), std::end(segmentR));
    }
    
    // to decode, use a monoalphabetic substitution char -> char
    std::map<char, char> decoder;
    std::string alpha1 = "abcdefg";
    std::string alpha2;
      
    ull total2 = 0;
    ull matches = 0;
    
    auto reorderSegments = [&](std::string shuffledSegment) {
        std::string segments = "";
        for(auto i = 0; i < shuffledSegment.size(); ++i)
            segments += decoder[shuffledSegment[i]];
        
        // important: sort the reordered segments to allow the comparison
        std::sort(std::begin(segments), std::end(segments));
        
        return segments;
    };
    
    for(auto const& segments : randomizedSegments) {
        alpha2 = alpha1; // start with no substitution at all: a -> a, etc.
        
        do {
            // setup the decoder using the current permutation of alpha2
            for(auto i = 0; i < alpha1.size(); ++i)
                decoder[alpha1[i]] = alpha2[i];
            
            matches = 0;
            
            // use the segments on the left to perform the analysis
            for(auto const& segmentL : segments.first) {
                
                auto reorderedSegments = reorderSegments(segmentL);
                    
                if (segmentsType.find(reorderedSegments) != segmentsType.end())
                    ++matches;
                else
                    break;
                
                // when a solution is found for this row of segment...
                if (matches == segments.first.size()) {
                    
                    // debug
                    std::cout << "Substitution for ";
                    for(auto s : segments.first)
                        std::cout << s << " ";
                    std::cout << "=> " << alpha1 << " <> " << alpha2 << std::endl;
                    
                    // ... reorder the segments on the right
                    std::string number = "";
                    for(auto const& segmentR : segments.second) {
                        auto reorderedSegments = reorderSegments(segmentR);
                        number += std::to_string(segmentsType[reorderedSegments]);
                    }
                    
                    total2 += std::stoi(number);
                }
            }
            
        } while(std::next_permutation(std::begin(alpha2), std::end(alpha2)));
    }

    std::cout << total2 << std::endl;
}

// -------------------- DAY 9 --------------------

void day9() {
    std::vector<std::string> ls;
    for(auto const& line : lines) {
        ls.emplace_back(line.getRawLine());
    }
    
    Matrix heightmap(ls[0].size(), ls.size());
    
    for(auto i = 0; i < heightmap.getSizeX(); ++i) {
        for(auto j = 0; j < heightmap.getSizeY(); ++j) {
            heightmap.setValue(i, j, ls[j][i] - '0');
        }
    }
    
    heightmap.show();
    
    // Part One
    separator("Day 9:A");
    
    ull riskLevel = 0;
    bool isLow = true;
    auto currentValue = 0;
    for(auto i = 0; i < heightmap.getSizeX(); ++i) {
        for(auto j = 0; j < heightmap.getSizeY(); ++j) {
            
            isLow = true;
            currentValue = heightmap.getValue(i, j);
            auto neighbors = heightmap.getFourNeighbors(i, j);
            
            for(auto const& neighbor : neighbors) {
                if (currentValue >= neighbor.second) {
                    isLow = false;
                    break;
                }
            }
            
            if (isLow)
                riskLevel += currentValue + 1;
        }
    }
    
    std::cout << riskLevel << std::endl;
    
    // Part Two
    separator("Day 9:B");

    // keep track of locations belonging to a basin
    std::map<Point, bool> belongingToBasin;
    
    // ignore locations based on their characteristics
    auto ignoreLocation = [&](Point const& location) {
        // > Locations of height 9 do not count as being in any basin
        if (heightmap.getValue(location.x, location.y) == 9)
            return true;
        
        // ignore locations already explored
        if (belongingToBasin.find(Point(location.x, location.y)) != belongingToBasin.end())
            return true;
        
        return false;
    };

    std::vector<std::vector<Point>> basins;
    std::stack<Point> toExplore;
    
    for(auto i = 0; i < heightmap.getSizeX(); ++i) {
        for(auto j = 0; j < heightmap.getSizeY(); ++j) {
            
            if (ignoreLocation(Point(i, j)))
                continue;
            
            toExplore.push(Point(i, j));
            std::vector<Point> currentBasin;
                        
            // explore from current position
            while(!toExplore.empty()) {
                auto current = toExplore.top();
                toExplore.pop();
                
                Point currentLocation(current.x, current.y);
                
                if (ignoreLocation(currentLocation))
                    continue;
                                
                currentBasin.emplace_back(currentLocation);
                
                // memorize this location to prevent exploring it in the future
                belongingToBasin[currentLocation] = true;
                            
                for(auto const& neighbor : heightmap.getFourNeighbors(current.x, current.y))
                    toExplore.push(Point(neighbor.first.x, neighbor.first.y));
            }
                        
            basins.emplace_back(currentBasin);
        }
    }
    
    // sort basins by size
    std::sort(std::begin(basins), std::end(basins),
              [] (std::vector<Point> const& a,  std::vector<Point> const &b) {
                  return a.size() > b.size();
              });
    
    ull total = 1;
    for(auto i = 0; i < 3; ++i)
        total *= basins[i].size();
    
    std::cout << total << std::endl;
}

// -------------------- DAY 10 --------------------

void day10() {
    std::vector<std::string> ls;
    for(auto const& line : lines) {
        ls.emplace_back(line.getRawLine());
    }
    
    auto getMatchingChunk = [](char c) {
        if (c == '(') return ')';
        if (c == ')') return '(';
        if (c == '[') return ']';
        if (c == ']') return '[';
        if (c == '{') return '}';
        if (c == '}') return '{';
        if (c == '<') return '>';
        if (c == '>') return '<';
        
        return c;
    };
   
    separator("Day 10:A");
    
    // classic brackets matching algorithm
    auto isCorrupted = [&](std::string chunks, char sentinelChar) {
        std::stack<char> ch;
        for(auto c : chunks) {
            switch(c) {
                case '(':
                case '[':
                case '{':
                case '<':
                    ch.push(c);
                    break;
            }
            
            if (ch.empty()) {
                return sentinelChar;
            }
        
            switch(c) {
                case ')':
                case ']':
                case '}':
                case '>':
                    auto x = ch.top();
                    ch.pop();
                    if (x != getMatchingChunk(c)) {
                        return c;
                    }
                    break;
            }
        }
        
        return sentinelChar;
    };
    
    std::vector<std::string> incomplete;
    std::map<char, int> corruptedPoints;
    const char sentinelChar = '\0';
    
    for(auto chunks : ls) {
        auto corruptedChar = isCorrupted(chunks, sentinelChar);
        if (corruptedChar != sentinelChar)
            ++corruptedPoints[corruptedChar];
        else
            incomplete.emplace_back(chunks);
    }
    
    ull total = 0;
    for(auto c : corruptedPoints) {
        if (c.first == ')')
            total += 3 * c.second;
        if (c.first == ']')
            total += 57 * c.second;
        if (c.first == '}')
            total += 1197 * c.second;
        if (c.first == '>')
            total += 25137 * c.second;
    }
    
    std::cout << total << std::endl;
    
    separator("Day 10:B");
    
    std::vector<std::string> completingParts;
    for(auto chunks : incomplete) {
        
        // delete pairs that are adjacently matching (e.g., '[]')
        // in order to identify the core incomplete part
        // (stop when no such pairs exist in the remaining string)
        auto incompletePart = chunks;
        while(true) {
            bool hasBeenErased = false;
            for(int i = static_cast<int>(incompletePart.size() - 1); i >= 0; --i) {
                if (incompletePart[i] == getMatchingChunk(incompletePart[i - 1])) {
                    incompletePart.erase(i, 1);
                    incompletePart.erase(i - 1, 1);
                    hasBeenErased = true;
                }
            }
            
            if (!hasBeenErased)
                break;
        }
        
        // now that the incomplete part has been identify, mirror it:
        // - first, by reversing it
        // - then, by inverting its components (e.g., '[' -> ']')
        std::reverse(std::begin(incompletePart), std::end(incompletePart));
        for(auto& c : incompletePart) c = getMatchingChunk(c);
        
        completingParts.emplace_back(incompletePart);
    }
    
    // score
    std::vector<ull> scores;
    for(auto const& completingPart : completingParts) {
        ull score = 0;
        for(auto c : completingPart) {
            score *= 5;
            if (c == ')') score += 1;
            if (c == ']') score += 2;
            if (c == '}') score += 3;
            if (c == '>') score += 4;
        }
        scores.emplace_back(score);
    }
    
    std::sort(std::begin(scores), std::end(scores));
    
    std::cout << scores[scores.size() / 2] << std::endl;
}

// -------------------- DAY 11 --------------------

void day11() {
    std::vector<std::string> ls;
    for(auto const& line : lines) {
        ls.emplace_back(line.getRawLine());
    }
    
    Matrix grid(ls[0].size(), ls.size());
    
    for(auto i = 0; i < ls[0].size(); ++i)
        for(auto j = 0; j < ls.size(); ++j)
            grid.setValue(i, j, ls[j][i] - '0');
        
    auto tryToFlash = [](int i, int j, std::map<Point, bool>& flashed, Matrix& grid) {
        auto value = grid.getValue(i, j);
        
        if (value > 9 && flashed.find(Point(i, j)) == flashed.end()) {
            flashed[Point(i, j)] = true;
            
            for(auto neighbor : grid.getAllNeighbors(i, j))
                grid.increment(neighbor.first.x, neighbor.first.y);
            
            return 1;
        }
        
        return 0;
    };
    
    auto areAllFlashing = [](Matrix& grid) {
        for(auto i = 0; i < grid.getSizeX(); ++i)
            for(auto j = 0; j < grid.getSizeY(); ++j)
                if (grid.getValue(i, j) != 0)
                    return false;
        
        return true;
    };
    
    auto performSteps = [&](Matrix grid, int numberOfSteps, bool show = false) {
        ull totalFlashesCount = 0;
        auto flashsCount = 0;
        std::map<Point, bool> flashed;
        
        if (numberOfSteps < 0)
            numberOfSteps = std::numeric_limits<int>::max();
        
        // steps start from 1, not 0
        for(auto steps = 1; steps <= numberOfSteps; ++steps) {
            flashed.clear();
            
            // > First, the energy level of each octopus increases by 1
            grid.incrementAll();
            
            do {
                
                flashsCount = 0;
                
                // > Then, any octopus with an energy level greater than 9 flashes...
                for(auto i = 0; i < grid.getSizeX(); ++i)
                    for(auto j = 0; j < grid.getSizeY(); ++j)
                        flashsCount += tryToFlash(i, j, flashed, grid);
                
                totalFlashesCount += flashsCount;
                
            } while(flashsCount > 0);
            
            // > Finally, any octopus that flashed during this step has its energy level
            // > set to 0, as it used all of its energy to flash
            for(auto i = 0; i < grid.getSizeX(); ++i)
                for(auto j = 0; j < grid.getSizeY(); ++j)
                    if (flashed.find(Point(i, j)) != flashed.end())
                        grid.setValue(i, j, 0);
            
            if (show) {
                std::cout << std::endl << "-- " << steps << " --" << std::endl;
                grid.show();
            }
            
            if (areAllFlashing(grid))
                return std::make_pair(totalFlashesCount, steps);
        }
        
        return std::make_pair(totalFlashesCount, numberOfSteps);
    };
    
    separator("Day 11:A");
    
    std::cout << performSteps(grid, 100, false).first << std::endl;
    
    separator("Day 11:B");
    
    std::cout << performSteps(grid, -1, true).second << std::endl;
}

// -------------------- DAY 12 --------------------

void day12() {
    class Graph {
        std::set<std::string> _vertices;
        std::map<std::string, std::vector<std::string>> _edges;
        
    public:
        void addEdge(std::string from, std::string to) {
            _edges[from].emplace_back(to);
            _edges[to].emplace_back(from);
            _vertices.insert(from);
            _vertices.insert(to);
        }
        
        void show() const {
            for(auto edge : _edges) {
                for(auto v : edge.second) {
                    std::cout << edge.first << " <-> " << v << std::endl;
                }
            }
        }
        
        std::vector<std::string> getConnectedNodes(std::string node) {
            return _edges[node];
        }
        
    };
    
    Graph graph;
    for(auto const& line : lines) {
        auto nodes = tokenize(line.getRawLine(), "-");
        graph.addEdge(nodes[0], nodes[1]);
    }
    
    graph.show();
    
    // TODO (redo the implementation
}

// -------------------- DAY 20 --------------------

void day20() {
    
    std::string imageEnhancementAlgorighm;
    std::vector<std::string> ls;
    auto i = 0;
    for(auto const& line : lines) {
        if (i == 0) {
            imageEnhancementAlgorighm = line.getRawLine();
        }
        else if (i > 1) {
            ls.emplace_back(line.getRawLine());
        }
        
        ++i;
    }
    
    auto binaryToInt = [](std::string bin) {
        return std::stoi(bin, nullptr, 2);
    };
    
    auto offset = 3;

    Matrix matrix(ls[0].size(), ls.size());
    
    for(auto i = 0; i < ls[0].size(); ++i)
        for(auto j = 0; j < ls.size(); ++j)
            matrix.setValue(i, j, 0);
    
    
    for(auto i = 0; i < ls[0].size(); ++i)
        for(auto j = 0; j < ls.size(); ++j)
            if (ls[j][i] == '#')
                matrix.setValue(i, j, 1);
    
    matrix.show();
    
    auto generateNewMatrix = [imageEnhancementAlgorighm](Matrix& currentMatrix) {

        // offset
        auto offset = 3;
        Matrix offsetMatrix(currentMatrix.getSizeX() + offset * 2, currentMatrix.getSizeY() + offset * 2);
        
        for(auto i = 0; i < currentMatrix.getSizeX(); ++i)
            for(auto j = 0; j < currentMatrix.getSizeY(); ++j)
                if (currentMatrix.getValue(i, j) == 1)
                    offsetMatrix.setValue(i + offset, j + offset, 1);

        // enlight
        Matrix newMatrix(offsetMatrix.getSizeX(), offsetMatrix.getSizeY());
        
        for(auto i = 0; i < offsetMatrix.getSizeX(); ++i) {
            for(auto j = 0; j < offsetMatrix.getSizeY(); ++j) {
                auto n = offsetMatrix.getAllNeighbors(i, j);
                
                if (n.size() == 8) {
                    std::string binaryNumber = "";
                    
                    for(auto i = 0; i < 4; ++i)
                            binaryNumber += std::to_string(n[i].second);
                    
                    binaryNumber += std::to_string(offsetMatrix.getValue(i, j));
                    
                    for(auto i = 4; i < 8; ++i)
                            binaryNumber += std::to_string(n[i].second);
                    
                    auto b = std::stoi(binaryNumber, nullptr, 2);
                    
                    auto status = imageEnhancementAlgorighm[b];
                    
                    if (status == '#')
                        newMatrix.setValue(i, j, 1);
                }
               
            }
        }
        
        return newMatrix;
    };
    
    auto m2 = generateNewMatrix(matrix);
    m2.show();
    
    auto m3 = generateNewMatrix(m2);
    m3.show();
    
    ull total = 0;
    for(auto i = 0; i < m3.getSizeX(); ++i)
        for(auto j = 0; j < m3.getSizeY(); ++j)
            if (m3.getValue(i, j) == 1)
                ++total;
    
    std::cout << total << std::endl;
                
    
    
}

// -------------------- CURRENT DAY --------------------

void today() {
    
    
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
        case 9:
            day9();
            break;
        case 10:
            day10();
            break;
        case 11:
            day11();
            break;
        case 12:
            day12();
            break;
        case 20:
            day20();
            break;
        default:
            std::cerr << "Day not implemented (" << std::to_string(day) << ")" << std::endl;
    }
}
