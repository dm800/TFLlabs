#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class DFA {
public:
    DFA(std::vector<std::unordered_map<char, int>> transitions,
        std::unordered_set<int> finals);

    bool run(const std::string& input) const;

private:
    std::vector<std::unordered_map<char, int>> transitions;
    std::unordered_set<int> finals;
};

bool run_automataDFA(const std::string& str);
