//
// Created by vivekdagar on 20/7/24.
//

#include "../../include/utils/Propagator.h"

#include <unordered_set>

std::unordered_set<char> propagate(const CFG& cfg) {
    std::unordered_set<char> temp;

    for (const auto &rule: cfg.toVector()) {
        temp.insert(rule.lhs);
        for (const auto &rhs: rule.rhs) {
            for (const auto &ch: rhs) {
                if (std::isupper(ch))
                    temp.insert(ch);
            }
        }
    }

    return temp;
}

char free(std::unordered_set<char> obj) {
    std::string nonTerminals = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (char ch: nonTerminals) {
        // Check if the character is used
        if (obj.find(ch) == obj.end()) return ch;
    }

    return '~'; // In case nothing is free
}