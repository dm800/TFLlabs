#include "AFA.h"

AFA::AFA(std::vector<std::unordered_map<char, std::vector<int>>> transitions,
         std::vector<std::vector<int>> epsTransitions,
         std::unordered_set<int> finals,
         std::unordered_set<int> andStates)
    : transitions(std::move(transitions)),
      epsTransitions(std::move(epsTransitions)),
      finals(std::move(finals)),
      andStates(std::move(andStates)) {}

bool AFA::eval(int state, int pos, const std::string& input) const {
    const int L = static_cast<int>(input.size());

    if (!isAnd(state)) {
        if (pos == L) {
            return finals.count(state) != 0;
        }

        char ch = input[pos];
        auto it = transitions[state].find(ch);
        if (it == transitions[state].end()) {
            return false;
        }

        for (int to : it->second) {
            if (eval(to, pos + 1, input)) {
                return true;
            }
        }
        return false;
    }

    bool hasAny = false;

    for (int to : epsTransitions[state]) {
        hasAny = true;
        if (!eval(to, pos, input)) {
            return false;
        }
    }

    if (pos < L) {
        char ch = input[pos];
        auto it = transitions[state].find(ch);
        if (it != transitions[state].end()) {
            for (int to : it->second) {
                hasAny = true;
                if (!eval(to, pos + 1, input)) {
                    return false;
                }
            }
        }
    }

    if (!hasAny) {
        return (pos == L && finals.count(state) != 0);
    }

    return true;
}

bool AFA::run(const std::string& input) const {
    return eval(0, 0, input);
}

bool run_automataAFA(const std::string& str) {
    const int N = 14;

    std::vector<std::unordered_map<char, std::vector<int>>> transitions(N);
    std::vector<std::vector<int>> epsTransitions(N);

    epsTransitions[0].push_back(1);
    epsTransitions[0].push_back(8);

    transitions[1]['a'].push_back(2);
    transitions[1]['b'].push_back(1);

    transitions[2]['b'].push_back(3);
    transitions[2]['a'].push_back(2);

    transitions[3]['a'].push_back(4);
    transitions[3]['b'].push_back(1);

    transitions[4]['b'].push_back(5);
    transitions[4]['a'].push_back(2);

    transitions[5]['a'].push_back(6);
    transitions[5]['b'].push_back(1);

    transitions[6]['b'].push_back(7);
    transitions[7]['b'].push_back(1);

    transitions[8]['a'].push_back(9);
    transitions[8]['a'].push_back(11);
    transitions[8]['b'].push_back(8);
    transitions[8]['b'].push_back(11);

    transitions[9]['a'].push_back(10);
    transitions[9]['b'].push_back(9);

    transitions[10]['a'].push_back(9);
    transitions[10]['a'].push_back(11);
    transitions[10]['b'].push_back(11);

    transitions[11]['a'].push_back(12);
    transitions[12]['b'].push_back(13);
    transitions[13]['b'].push_back(10);

    std::unordered_set<int> finals;
    finals.insert(8);
    finals.insert(10);
    finals.insert(1);
    finals.insert(2);
    finals.insert(3);
    finals.insert(4);

    std::unordered_set<int> andStates;
    andStates.insert(0);

    AFA afa(std::move(transitions), std::move(epsTransitions),
            std::move(finals), std::move(andStates));

    return afa.run(str);
}

