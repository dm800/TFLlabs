#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class AFA {
public:
    AFA(std::vector<std::unordered_map<char, std::vector<int>>> transitions,
        std::vector<std::vector<int>> epsTransitions,
        std::unordered_set<int> finals,
        std::unordered_set<int> andStates);

    bool run(const std::string& input) const;

private:
    std::vector<std::unordered_map<char, std::vector<int>>> transitions;
    std::vector<std::vector<int>> epsTransitions;
    std::unordered_set<int> finals;
    std::unordered_set<int> andStates;

    bool isAnd(int s) const { return andStates.count(s) != 0; }

    bool eval(int state, int pos, const std::string& input) const;
};

bool run_automataAFA(const std::string& str);
