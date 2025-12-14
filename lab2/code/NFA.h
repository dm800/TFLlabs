#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class NFA {
public:
    NFA(std::vector<std::unordered_map<char, std::vector<int>>> transitions,
        std::unordered_set<int> finals);

    bool run(const std::string& input) const;

private:
    std::vector<std::unordered_map<char, std::vector<int>>> transitions;
    std::unordered_set<int> finals;
};

bool run_automataNFA(const std::string& str);
