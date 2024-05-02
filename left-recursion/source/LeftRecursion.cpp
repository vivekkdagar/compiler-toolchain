//
// Created by vivekdagar on 01/05/24.
//

#include <algorithm>
#include "../include/LeftRecursion.h"

LeftRecursion::LeftRecursion(const rule &production) : production(production) {
    for (const auto &obj: this->production.rhs) {
        for (const auto &ch: obj) {
            if (std::isupper(ch))
                usedNonTerminals.insert(ch);
        }
    }
    usedNonTerminals.insert(this->production.lhs);
}

void LeftRecursion::convert() {
    rearrangeStartingWith(production.rhs, production.lhs);

    // No left recursion
    if (production.rhs[0][0] not_eq production.lhs)
        return;

    char free = pickFree();
    this->usedNonTerminals.insert(free);

    if(free == '~') {
        throw std::runtime_error("No non terminals are free");
    }

    if (this->production.rhs.size() == 2) {
        std::string suffix = production.rhs[0].substr(1);

        rightRecursiveCFG.addRule(this->production.lhs, production.rhs[1] + free);
        rightRecursiveCFG.addRule(free, suffix + free);
        rightRecursiveCFG.addRule(free, "#");

        return;
    }

    if (this->production.rhs[1][0] not_eq this->production.lhs) {
        for (int i{1}; i < this->production.rhs.size(); i++) {
            rightRecursiveCFG.addRule(this->production.lhs, this->production.rhs[i] + free);
        }

        std::string suffix = production.rhs[0].substr(1, production.rhs[0].size());

        rightRecursiveCFG.addRule(free, suffix + free);
        rightRecursiveCFG.addRule(free, "#");
        return;
    }

    for (auto &rh: this->production.rhs) {
        if (rh[0] not_eq production.lhs) {
            rightRecursiveCFG.addRule(this->production.lhs, rh + free);
        }
    }

    rightRecursiveCFG.addRule(free, "#");

    for (int i{0}; i < this->production.rhs.size(); i++) {
        if (this->production.rhs[i][0] not_eq this->production.lhs) {
            break;
        } else {
            std::string suffix = production.rhs[i].substr(1);
            rightRecursiveCFG.addRule(free, suffix + free);
        }
    }
}

void LeftRecursion::rearrangeStartingWith(vector<std::string> &vec, char startChar) {
    auto it = std::partition(vec.begin(), vec.end(), [startChar](const std::string &str) {
        return str.front() == startChar;
    });
}

char LeftRecursion::pickFree() {
    std::string nonTerminals = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (char ch: nonTerminals) {
        if (usedNonTerminals.find(ch) == usedNonTerminals.end()) {
            return ch;
        }
    }

    return '~';
}

const CFG &LeftRecursion::getRightRecursiveCfg() const {
    return rightRecursiveCFG;
}
