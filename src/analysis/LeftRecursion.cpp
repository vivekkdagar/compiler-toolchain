//
// Created by vivekdagar on 20/7/24.
//

#include "../../include/analysis/LeftRecursion.h"
#include <algorithm>
#include "../../include/utils/Propagator.h"

void LeftRecursion::convert() {
    for (auto &r: input.toVector()) {
        production = r;

        rearrangeStartingWith(production.rhs, production.lhs);

        // No left recursion
        if (production.rhs[0][0] not_eq production.lhs) {
            for (const auto &obj: production.rhs) {
                result.addRule(production.lhs, obj);
            }
            continue;
        }

        char freeChr = free(usedNonTerminals);

        this->usedNonTerminals.insert(freeChr);
        if (freeChr == '~') {
            throw std::runtime_error("No non terminals are free");
        }
        if (this->production.rhs.size() == 2) {
            std::string suffix = production.rhs[0].substr(1);
            result.addRule(this->production.lhs,
                           production.rhs[1] + freeChr);
            result.addRule(freeChr, suffix + freeChr);
            result.addRule(freeChr, "#");
            continue;
        }
        if (this->production.rhs[1][0] not_eq this->production.lhs) {
            for (int i{1}; i < this->production.rhs.size(); i++) {
                result.addRule(this->production.lhs,
                               this->production.rhs[i] + freeChr);
            }
            std::string suffix = production.rhs[0].substr(1,
                                                          production.rhs[0].size());
            result.addRule(freeChr, suffix + freeChr);
            result.addRule(freeChr, "#");
            continue;
        }
        for (auto &rh: this->production.rhs) {
            if (rh[0] not_eq production.lhs) {
                result.addRule(this->production.lhs, rh +
                                                     freeChr);
            }
        }
        result.addRule(freeChr, "#");
        for (int i{0}; i < this->production.rhs.size(); i++) {
            if (this->production.rhs[i][0] not_eq this->production.lhs)
                break;
            else {
                std::string suffix = production.rhs[i].substr(1);
                result.addRule(freeChr, suffix + freeChr);
            }
        }
    }
}

void LeftRecursion::rearrangeStartingWith(vector<std::string> &vec,
                                          char startChar) {
    auto it = std::partition(vec.begin(), vec.end(),
                             [startChar](const std::string &str) {
                                 return str.front() == startChar;
                             });
}

LeftRecursion::LeftRecursion(const CFG &cfg) {
    usedNonTerminals = propagate(cfg);
    input = cfg;
}
