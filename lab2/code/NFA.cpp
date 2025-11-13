#include "NFA.h"


bool Nq0(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Nq1(str, cur + 1) or Nq3(str, cur + 1);
    }
    return Nq0(str, cur + 1) or Nq3(str, cur + 1);
}

bool Nq1(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Nq2(str, cur + 1);
    }
    return Nq1(str, cur + 1);
}

bool Nq2(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return true;
    }
    if (str[cur] == 'a') {
        return Nq1(str, cur + 1) or Nq3(str, cur + 1);
    }
    return Nq3(str, cur + 1);
}

bool Nq3(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return Nq4(str, cur + 1);
    }
    return false;
}

bool Nq4(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return false;
    }
    return Nq5(str, cur + 1);
}

bool Nq5(std::string& str, size_t cur) {
    if (cur == str.length()) {
        return false;
    }
    if (str[cur] == 'a') {
        return false;
    }
    return Nq2(str, cur + 1);
}

bool run_automataNFA(std::string& str) {
    return Nq0(str, 0);
}
