#include "NFA.h"
#include "DFA.h"
#include "AFA.h"
#include <iostream>
#include <random>
#include <string>
#include <regex>
#define CORRECT_TESTS_COUNT 10
#define STRING_LENGTH_LOW 10
#define STRING_LENGTH_HIGH 20


std::vector<std::vector<double> > chances = {
    {0.5, 0.5},
    {0.4, 0.6}
};

std::random_device rd;
std::vector<std::string> letters = {"a", "b"};

char pick_random(const char prev) {
    std::string ref = "ab";
    size_t index = ref.find(prev);
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float val = dist(rd);
    int ind = 0;
    double s = 0;
    while (true) {
        s += chances[index][ind];
        if (s > val) {
            break;
        }
        ind++;
    }
    return ref[ind];
}


std::string pseudo_random(int length) {
    int size = 1;
    std::string answer;
    std::uniform_int_distribution<int> dist(0, letters.size() - 1);
    answer = letters[dist(rd)];
    while (size < length) {
        answer += pick_random(answer.back());
        size++;
    }
    return answer;
}

// регулярка: b*((ab*a)*(aabb|(babb)*))*
// extended: ^(?=[ab]*$)b*((ab*a)|(.abb))*$

std::regex normal = std::regex("b*((ab*a)*(aabb|(babb)*))*");
std::regex extended = std::regex("^b*((ab*a)|(.abb))*$", std::regex_constants::extended);

int main() {
    int c = 0;
    std::uniform_int_distribution<int> dist(STRING_LENGTH_LOW, STRING_LENGTH_HIGH);
    bool tr = false;
    for (int i = 0; i < CORRECT_TESTS_COUNT; (tr == 1) ? i++ : i) {
        tr = false;
        std::string str = pseudo_random(dist(rd));
        bool reg = std::regex_match(str, normal);
        bool DFA = run_automataDFA(str);
        bool NFA = run_automataNFA(str);
        bool AFA = run_automataAFA(str);
        bool EXT = std::regex_match(str, extended);
        std::cout << reg << " " << DFA << " " << NFA << " " << AFA << " " << EXT << " " << str << std::endl;
        if ((reg != DFA) or (reg != NFA) or (reg != EXT) or (reg != AFA)) {
            std::cout << "FOUND ERROR\nreg: " << reg << "\nDFA: " << DFA << "\nNFA: " << NFA << "\nAFA:" << AFA << "\nEXT: " << EXT << std::endl;
            c++;
        }
        if (reg == 1) {
            tr = true;
        }
    }
    if (c != 0) {
        std::cout << "TEST FAILED" << std::endl;
    } else {
        std::cout << "TEST PASSED" << std::endl;
    }

    return 0;
}
