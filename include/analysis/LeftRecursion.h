//
// Created by vivekdagar on 20/7/24.
//

#ifndef LEFTRECURSION_H
#define LEFTRECURSION_H

#include <unordered_set>
#include "../grammar/CFG.h"

class LeftRecursion {
    CFG result;
    CFG input;
    std::unordered_set<char> usedNonTerminals;

public:
    explicit LeftRecursion(const CFG &cfg);

    void convert();

    const CFG &output() const {
        return result;
    }

private:
    rule production;

    static void rearrangeStartingWith(std::vector<std::string> &vec,
                                      char startChar);
};


#endif //LEFTRECURSION_H
