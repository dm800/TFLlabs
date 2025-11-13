#include "DFA.h"

bool run_automataDFA(std::string& str) {
    return Dq0(str, 0);
}

bool Dq0(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Dq1(str, cur + 1);
    }
    return Dq2(str, cur + 1);
}

bool Dq1(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq3(str, cur + 1);
    }
    return Dq4(str, cur + 1);
}

bool Dq2(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Dq5(str, cur + 1);
    }
    return Dq2(str, cur + 1);
}

bool Dq3(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Dq1(str, cur + 1);
    }
    return Dq6(str, cur + 1);
}

bool Dq4(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq7(str, cur + 1);
    }
    return Dq4(str, cur + 1);
}

bool Dq5(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq3(str, cur + 1);
    }
    return Dq8(str, cur + 1);
}

bool Dq6(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq9(str, cur + 1);
    }
    return Dq7(str, cur + 1);
}

bool Dq7(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Dq1(str, cur + 1);
    }
    return Dq10(str, cur + 1);
}

bool Dq8(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq7(str, cur + 1);
    }
    return Dq11(str, cur + 1);
}

bool Dq9(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq12(str, cur + 1);
    }
    return Dq13(str, cur + 1);
}

bool Dq10(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq9(str, cur + 1);
    }
    return Dq12(str, cur + 1);
}

bool Dq11(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Dq14(str, cur + 1);
    }
    return Dq1(str, cur + 1);
}

bool Dq12(std::string& str, size_t cur) {
    return false;
}

bool Dq13(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq12(str, cur + 1);
    }
    return Dq7(str, cur + 1);
}

bool Dq14(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Dq15(str, cur + 1);
    }
    return Dq1(str, cur + 1);
}

bool Dq15(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Dq15(str, cur + 1);
    }
    return Dq16(str, cur + 1);
}

bool Dq16(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Dq3(str, cur + 1);
    }
    return Dq11(str, cur + 1);
}
