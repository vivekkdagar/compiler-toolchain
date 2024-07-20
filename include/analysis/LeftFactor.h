//
// Created by vivekdagar on 20/7/24.
//

#ifndef LEFTFACTOR_H
#define LEFTFACTOR_H

#include <unordered_set>
#include "../grammar/CFG.h"
#include "../../include/utils/Propagator.h"
#include <algorithm>

class LeftFactor {
    CFG input;
    std::unordered_set<char> usedNonTerminals;

public:
    explicit LeftFactor(const CFG &cfg);

    void factor();

    const CFG &output() const {
        return result;
    }

private:
    CFG result;

    rule production;

    static std::string findCommonSubstring(const
        std::vector<std::string> &substrings);
};


#endif //LEFTFACTOR_H
