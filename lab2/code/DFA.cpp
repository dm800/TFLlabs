#include "DFA.h"

DFA::DFA(std::vector<std::unordered_map<char, int>> transitions,
         std::unordered_set<int> finals) {
    this->transitions = std::move(transitions);
    this->finals = std::move(finals);
}

bool DFA::run(const std::string& input) const {
    int state = 0;

    for (char ch : input) {

        const std::unordered_map<char, int>& mp = this->transitions[state];
        auto it = mp.find(ch);

        if (it == mp.end()) {
            return false;
        }

        state = it->second;
    }

    if (this->finals.find(state) != this->finals.end()) {
        return true;
    }

    return false;
}

bool run_automataDFA(const std::string& str) {
    std::vector<std::unordered_map<char, int>> transitions(17);

    // q0
    transitions[0]['a'] = 1;
    transitions[0]['b'] = 2;

    // q1
    transitions[1]['a'] = 3;
    transitions[1]['b'] = 4;

    // q2
    transitions[2]['a'] = 5;
    transitions[2]['b'] = 2;

    // q3
    transitions[3]['a'] = 1;
    transitions[3]['b'] = 6;

    // q4
    transitions[4]['a'] = 7;
    transitions[4]['b'] = 4;

    // q5
    transitions[5]['a'] = 3;
    transitions[5]['b'] = 8;

    // q6
    transitions[6]['a'] = 9;
    transitions[6]['b'] = 7;

    // q7
    transitions[7]['a'] = 1;
    transitions[7]['b'] = 10;

    // q8
    transitions[8]['a'] = 7;
    transitions[8]['b'] = 11;

    // q9
    transitions[9]['a'] = 12;
    transitions[9]['b'] = 13;

    // q10
    transitions[10]['a'] = 9;
    transitions[10]['b'] = 12;

    // q11
    transitions[11]['a'] = 14;
    transitions[11]['b'] = 1;

    // q12
    transitions[12]['a'] = 12;
    transitions[12]['b'] = 12;

    // q13
    transitions[13]['a'] = 12;
    transitions[13]['b'] = 7;

    // q14
    transitions[14]['a'] = 15;
    transitions[14]['b'] = 1;

    // q15
    transitions[15]['a'] = 15;
    transitions[15]['b'] = 16;

    // q16
    transitions[16]['a'] = 3;
    transitions[16]['b'] = 11;

    std::unordered_set<int> finals;
    finals.insert(0);
    finals.insert(2);
    finals.insert(3);
    finals.insert(7);
    finals.insert(11);
    finals.insert(14);
    finals.insert(15);

    DFA dfa(std::move(transitions), std::move(finals));
    return dfa.run(str);
}
