//
// Created by vivekdagar on 20/7/24.
//

#include "../../include/analysis/LeftFactor.h"

LeftFactor::LeftFactor(const CFG &cfg) {
    usedNonTerminals = propagate(cfg);
    input = cfg;
}

std::string LeftFactor::findCommonSubstring(const std::vector<std::string> &substrings) {
    if (substrings.empty()) return ""; // If no substrings, return empty string
    std::string commonSubstring = substrings[0]; // Initialize with the first substring

    // Iterate through the substrings to find common parts
    for (const auto &substring: substrings) {
        // Find the common part between the current substring and the commonSubstring
        size_t i = 0;
        while (i < commonSubstring.size() && i < substring.size() &&
               commonSubstring[i] == substring[i]) {
            i++;
        }
        commonSubstring = commonSubstring.substr(0, i); // Update the common substring
    }
    return commonSubstring;
}

void LeftFactor::factor() {
    for (const auto &rule: input.toVector()) {
        this->production = rule;
        std::sort(this->production.rhs.begin(),
                  this->production.rhs.end());

        // Initialize variables and loop through the production rules
        size_t len = this->production.rhs.size();
        int i{0};
        while (i < len) {
            vector<string> temp;
            const auto initial = this->production.rhs.at(i)[0];
            int j{i}, count{0};

            // Collect all productions starting with the same character
            while (j <= len - 1 and production.rhs.at(j).at(0) == initial) {
                temp.push_back(production.rhs.at(j));
                count++;
                j++;
            }

            // Handle the case where there is only one production
            if (count == 1) {
                if (not result.locate(production.lhs, production.rhs.at(i)))
                    this->result.addRule(this->production.lhs, production.rhs.at(i));
                i++;
                continue;
            }

            // Move index to the next group of productions
            i = j;

            // Find the common substring and pick a free character for new rules
            std::string common = findCommonSubstring(temp);
            char freeChar = free(usedNonTerminals);

            usedNonTerminals.insert(freeChar); // Mark the free character as used
            if (freeChar == '~')
                throw std::runtime_error("All non terminals used. this will cause redundancy");

            // Add the new rule with the common substring
            if (not result.locate(production.lhs, common + freeChar))
                this->result.addRule(this->production.lhs, common + freeChar);

            // Add rules for the remaining parts of the productions
            int k{0};
            if (temp[0] == common) {
                if (not result.locate(freeChar, "#"))
                    result.addRule(freeChar, "#");
                k = 1;
            }
            while (k < temp.size()) {
                temp[k].erase(0, common.length());
                if (not result.locate(freeChar, temp[k]))
                    result.addRule(freeChar, temp[k]);
                k++;
            }
        }
    }
}
