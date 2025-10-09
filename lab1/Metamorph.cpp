#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#define TESTS_COUNT 20
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


int count(const std::string &src, const std::string &pat) {
    int counter = 0;
    int t = pat.size();
    for (int i = 0; i < src.size() - t + 1; i++) {
        if (src.substr(i, t) == pat) {
            counter++;
        }
    }
    return counter;
}


bool check_for_inv(const std::string &prev, const std::string &current) {
    // Первый инвариант - длина
    if (prev.size() != current.size()) {
        return false;
    }
    // Второй - считаем дельту по буквам с и по буквам а. (Дельта а - дельта с) % 3 == 0.
    int delta_a = count(current, "a") - count(prev, "a");
    int delta_c = count(current, "c") - count(prev, "c");
    if ((delta_a - delta_c) % 3 != 0) {
        return false;
    }
    return true;
}


bool check_all_forms(const std::string &prev, const std::string &current,
            const std::vector<std::string> *rulesleft,
            const std::vector<std::string> *rulesright) {
    if (!prev.empty() && !check_for_inv(prev, current)) {
        return false;
    }
    bool result = true;
    bool found = false;
    for (int rulesind = 0; rulesind != rulesleft->size(); rulesind++) {
        const std::string &key = rulesleft->at(rulesind);
        std::vector<size_t> indexes = find_subs(current, key);
        if (!indexes.empty()) {
            found = true;
            for (auto ind: indexes) {
                std::string nstr = current;
                nstr.replace(ind, key.size(), rulesright->at(rulesind));
                result = result && check_all_forms(current, nstr, rulesleft, rulesright);
            }
        }
    }
    if (found == true) {
        return result;
    }
    return true;
}


int main() {
    int count = 0;
    int correct = 0;
    std::cout << "Starting " << TESTS_COUNT << " tests" << std::endl;
    while (count < TESTS_COUNT) {
        std::string generated = pseudo_random(STRING_LENGTH);
        bool checker = check_all_forms("", generated, &rulesleft1, &rulesright1);
        if (!checker) {
            std::cout << generated;
            break;
        }
        // проверка, что инвариант работает на строке с изначальными правилами
        bool result = check_all_forms("", generated, &rulesleft2, &rulesright2);
        if (result == true) {
            correct++;
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