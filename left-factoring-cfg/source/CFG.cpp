//
// Created by vivekdagar on 01/05/24.
//

#include "../include/CFG.h"

void CFG::addRule(char lhs, const std::string &text) {
    if (not isupper(lhs))
        return;

    bool found{false};

    for (auto &r: this->prods) {
        // If a rule with the same left-hand side is found
        if (r.lhs == lhs) {
            // Add the new production to its right-hand side
            r.rhs.push_back(text);
            found = true;
            break;
        }
    }

    // If no rule with the same left-hand side is found, create a new rule
    if (not found) {
        rule newRule;
        newRule.lhs = lhs;
        newRule.rhs.push_back(text);
        prods.push_back(newRule);
    }
}