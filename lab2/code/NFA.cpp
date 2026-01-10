#include "NFA.h"

#include <algorithm>

NFA::NFA(std::vector<std::unordered_map<char, std::vector<int>>> transitions,
         std::unordered_set<int> finals):
transitions(std::move(transitions)),
finals(std::move(finals)) {}

bool NFA::run(const std::string& input) const {
    std::unordered_set<int> cur;
    cur.insert(0);

    for (char ch : input) {
        std::unordered_set<int> next;

        for (int s : cur) {
            const std::unordered_map<char, std::vector<int>>& mp = transitions[s];
            auto it = mp.find(ch);

            if (it == mp.end()) {
                continue;
            }

            const std::vector<int>& tos = it->second;
            for (int to : tos) {
                next.insert(to);
            }
        }

        cur = std::move(next);

        if (cur.empty()) {
            return false;
        }
    }

    return std::any_of(cur.begin(), cur.end(),
        [&](int s) { return finals.count(s) != 0; });

}

bool run_automataNFA(const std::string& str) {
    std::vector<std::unordered_map<char, std::vector<int>>> transitions(6);

    transitions[0]['a'].push_back(1);
    transitions[0]['a'].push_back(3);
    transitions[0]['b'].push_back(0);
    transitions[0]['b'].push_back(3);

    transitions[1]['a'].push_back(2);
    transitions[1]['b'].push_back(1);

    transitions[2]['a'].push_back(1);
    transitions[2]['a'].push_back(3);
    transitions[2]['b'].push_back(3);

    transitions[3]['a'].push_back(4);

    transitions[4]['b'].push_back(5);

    transitions[5]['b'].push_back(2);

    std::unordered_set<int> finals;
    finals.insert(0);
    finals.insert(2);

    NFA nfa(std::move(transitions), std::move(finals));
    return nfa.run(str);
}
