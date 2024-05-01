//
// Created by vivekdagar on 01/05/24.
//

#ifndef LEFT_FACTORING_CFG_LEFTFACTORER_H
#define LEFT_FACTORING_CFG_LEFTFACTORER_H

#include <unordered_set>
#include "CFG.h"

class LeftFactor {
    rule production;
    std::unordered_set<char> usedNonTerminals;
    CFG leftFactoredCFG;
public:
    explicit LeftFactor(rule production);

    void factor();

    const CFG &getLeftFactoredCfg() const;

    void setProduction(const rule &prod);

private:
    static std::string findCommonSubstring(const std::vector<std::string> &substrings);

    char pickFree();
};


#endif //LEFT_FACTORING_CFG_LEFTFACTORER_H
