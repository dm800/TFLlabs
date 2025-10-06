#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#define TESTS_COUNT 100
#define STRING_LENGTH 10


std::random_device rd;

std::vector<std::string> rulesleft1 = {
    "bcab",
    "cccc",
    "abc",
    "bbb",
    "ccc",
    "abcabc"
};
std::vector<std::string> rulesright1 = {
    "bbbb",
    "cabc",
    "aaa",
    "abc",
    "abc",
    "aabbcc"
}; // правила изначальной TRS
std::vector<std::string> rulesleft2 = {
    "bcab",
    "cccc",
    "abc",
    "bbb",
    "ccc",
    "abcabc",
    "baaa",
    "caaa",
    "aaacc",
    "aaabab",
    "aaabbc",
    "aaacab",
    "aaacbc",
    "aabbcc",
    "aaaaabb",
    "aaabaac",
    "aaabacc",
    "aaabbaa",
    "aaabbab",
    "aaacacc",
    "aaacbab",
    "aaacbbc"
};
std::vector<std::string> rulesright2 = {
    "bbbb",
    "cabc",
    "aaa",
    "abc",
    "abc",
    "aabbcc",
    "aaab",
    "aaac",
    "aaaab",
    "aaaaac",
    "aaabaa",
    "aaaaaa",
    "aaacaa",
    "aaaaaa",
    "aaaaaac",
    "aaaaaaa",
    "aaabaab",
    "aaaaaac",
    "aaaaaaa",
    "aaacaab",
    "aaacaac",
    "aaacbaa"
}; // правила итоговой TRS

std::vector<std::string> letters = {"a", "b", "c"};

std::vector<std::vector<double> > chances = {
    {0.2, 0.6, 0.2},
    {0.2, 0.4, 0.4},
    {0.4, 0.2, 0.4}
};

char pick_random(const char prev) {
    std::string ref = "abc";
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
    std::uniform_int_distribution<int> dist(0, 2);
    answer = letters[dist(rd)];
    while (size < length) {
        answer += pick_random(answer.back());
        size++;
    }
    return answer;
}

std::vector<size_t> find_subs(const std::string &src, const std::string &pat) {
    std::vector<size_t> result = {};
    size_t ind = src.find(pat);
    while (ind != std::string::npos) {
        result.push_back(ind);
        ind += 1;
        ind = src.find(pat, ind);
    }
    return result;
}

std::vector<std::string> normals(const std::string &starting, const std::vector<std::string> *rulesleft,
                                 const std::vector<std::string> *rulesright) {
    std::vector<std::string> norms = {};
    bool found = false;
    for (int rulesind = 0; rulesind != rulesleft->size(); rulesind++) {
        const std::string &key = rulesleft->at(rulesind);
        std::vector<size_t> indexes = find_subs(starting, key);
        if (!indexes.empty()) {
            found = true;
            for (auto ind: indexes) {
                std::string nstr = starting;
                nstr.replace(ind, key.size(), rulesright->at(rulesind));
                std::vector<std::string> another = normals(nstr, rulesleft, rulesright);
                for (const auto &elem: another) {
                    if (!std::ranges::contains(norms, elem)) {
                        norms.push_back(elem);
                    }
                }
            }
        }
    }
    if (!found) {
        norms.push_back(starting);
    }
    return norms;
}

int main() {
    int count = 0;
    int correct = 0;
    std::cout << "Starting " << TESTS_COUNT << " tests" << std::endl;
    while (count < TESTS_COUNT) {
        std::string starting = pseudo_random(STRING_LENGTH);
        std::vector<std::string> result = normals(starting, &rulesleft1, &rulesright1);
        std::uniform_int_distribution<int> dist(0, result.size() - 1);
        const std::string &checking = result[dist(rd)];
        std::vector<std::string> norms1 = normals(starting, &rulesleft2, &rulesright2);
        std::vector<std::string> norms2 = normals(checking, &rulesleft2, &rulesright2);
        for (const auto &i: norms2) {
            if (std::ranges::contains(norms1, i)) {
                correct++;
                break;
            }
        }
        count++;
    }
    if (count == correct) {
        std::cout << "Everything passed the test" << std::endl;
    } else {
        std::cout << "Passed " << correct << "out of " << count << std::endl;
    }
    return 0;
}
