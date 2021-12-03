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
    separator("Day1:A");
    
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
    separator("Day1:B");

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
    separator("Day2:A");
    
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
    separator("Day2:B");
    
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
    separator("Day3:A");
    
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
    separator("Day3:B");
    
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
    
}

void solve(unsigned int day) {
    getInputTokens(day);
    
    switch(day) {
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
        default:
            std::cerr << "Day not implemented (" << std::to_string(day) << ")" << std::endl;
    }
}
