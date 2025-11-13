#include "NFA.h"
#include "DFA.h"
#include <iostream>
#include <string>
#include <regex>

// регулярка: b*((ab*a)*(aabb|(babb)*))*

int main() {

    std::string str = "aabb";
    std::regex_match(str, std::regex("b*((ab*a)*(aabb|(babb)*))*"));
    std::cout << std::regex_match(str, std::regex("b*((ab*a)*(aabb|(babb)*))*")) << " " << run_automataDFA(str) << " " << run_automataNFA(str) << std::endl;

    return 0;
}
