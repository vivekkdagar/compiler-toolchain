//
// Created by vivekdagar on 01/05/24.
//

#include <algorithm>
#include <utility>
#include "../include/LeftFactorer.h"

void LeftFactor::factor() {

    size_t len = this->production.rhs.size();
    int i{0};
    while (i < len) {
        vector<string> temp;
        char initial = this->production.rhs.at(i)[0];

        int j{i}, count{0};

        while (j <= len - 1 and production.rhs.at(j).at(0) == initial) {
            temp.push_back(production.rhs.at(j));
            count++;
            j++;
        }

        if (count == 1) {
            this->leftFactoredCFG.addRule(this->production.lhs, production.rhs.at(i));
            i++;
            continue;
        }

        i = j;

        std::string common = findCommonSubstring(temp);
        char freeChar = pickFree();
        usedNonTerminals.insert(freeChar); // Mark the free character as used

        if (freeChar == '~')
            throw std::runtime_error("All non terminals used. this will cause redundancy");

        this->leftFactoredCFG.addRule(this->production.lhs, common + freeChar);

        int k{0};
        if (temp[0] == common) {
            leftFactoredCFG.addRule(freeChar, "#");
            k = 1;
        }

        while (k < temp.size()) {
            temp[k].erase(0, common.length());
            leftFactoredCFG.addRule(freeChar, temp[k]);
            k++;
        }
    }
}

std::string LeftFactor::findCommonSubstring(const vector<std::string> &substrings) {
    if (substrings.empty()) return ""; // If no substrings, return empty string

    std::string commonSubstring = substrings[0]; // Initialize with the first substring

    // Iterate through the substrings to find common parts
    for (const auto &substring: substrings) {
        // Find the common part between the current substring and the commonSubstring
        size_t i = 0;
        while (i < commonSubstring.size() && i < substring.size() && commonSubstring[i] == substring[i]) {
            i++;
        }
        commonSubstring = commonSubstring.substr(0, i); // Update the common substring
    }

    return commonSubstring;
}

char LeftFactor::pickFree() {
    // Define the set of non-terminal characters
    std::string nonTerminals = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Iterate through each non-terminal character
    for (char ch: nonTerminals) {
        // Check if the character is used
        if (usedNonTerminals.find(ch) == usedNonTerminals.end()) {
            // If not used, mark it as used and return it
            return ch;
        }
    }

    // Return a default character if all non-terminals are used
    return '~'; // You can return any default character here
}

void LeftFactor::setProduction(const rule &prod) {
    LeftFactor::production = prod;
}

const CFG &LeftFactor::getLeftFactoredCfg() const {
    return leftFactoredCFG;
}

LeftFactor::LeftFactor(rule production) : production(std::move(production)) {
    for (const auto &obj: this->production.rhs) {
        for (const auto &ch: obj) {
            if (std::isupper(ch))
                usedNonTerminals.insert(ch);
        }
    }
    usedNonTerminals.insert(this->production.lhs);
    std::sort(this->production.rhs.begin(), this->production.rhs.end());
}
