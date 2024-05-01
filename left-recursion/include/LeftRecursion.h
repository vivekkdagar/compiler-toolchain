//
// Created by vivekdagar on 01/05/24.
//

#ifndef LEFT_RECURSION_LEFTRECURSION_H
#define LEFT_RECURSION_LEFTRECURSION_H


#include <unordered_set>
#include "CFG.h"

class LeftRecursion {
    rule production;
    CFG rightRecursiveCFG;
    std::unordered_set<char> usedNonTerminals;
public:
    explicit LeftRecursion(const rule &production);

    void convert();

    const CFG &getRightRecursiveCfg() const;

private:
    static void rearrangeStartingWith(std::vector<std::string>& vec, char startChar);

    char pickFree();
};


#endif //LEFT_RECURSION_LEFTRECURSION_H
