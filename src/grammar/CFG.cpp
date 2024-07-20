//
// Created by vivekdagar on 20/7/24.
//
#include <sstream>
#include "../../include/grammar/CFG.h"


void CFG::write(std::ostream &os) const {
    for (auto &r: this->prods) {
        os << r.lhs << " -> ";

        if (r.rhs.size() == 1)
            os << r.rhs.at(0);
        else {
            for (size_t j{0}; j < r.rhs.size(); j++) {
                os << r.rhs.at(j);
                if (j not_eq r.rhs.size() - 1)
                    os << " | ";
            }
        }
        os << std::endl;
    }
}

void CFG::read(std::istream &is) {
    std::string input;

    std::cout << "Enter strings (type 'exit' to quit):\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input not_eq "exit") {
            rule temp;
            bool valid{false};
            if (input.length() == 1 and std::isupper(input[0])) {
                temp.lhs = input[0];
            } else {
                std::istringstream iss(input);
                std::string word;
                while (iss >> word) {
                    if (word[0] not_eq ' ') {
                        valid = true;
                        temp.rhs.push_back(word);
                    }
                }
            }
            if (valid)
                prods.push_back(temp);
            continue;
        }
        break;
    }
}

void CFG::addRule(char lhs, const string &text) {
    if (not isupper(lhs))
        return;

    bool found{false};
    bool broken{false};

    for (auto &r: this->prods) {
        if (r.lhs == lhs) {
            for (auto &t: r.rhs) {
                if (t == text)
                    found = true;
            }

            if (not found) {
                r.rhs.push_back(text);
                broken = true;
                break;
            }
        }
    }

    if (not broken and not found) {
        rule newRule;
        newRule.lhs = lhs;
        newRule.rhs.push_back(text);
        prods.push_back(newRule);
    }
}

bool CFG::locate(char lhs, const string &text) {
    if (not isupper(lhs))
        throw std::runtime_error("LHS must be uppercase.");

    for (auto &r: this->prods) {
        if (r.lhs == lhs) {
            for (auto &t: r.rhs) {
                if (t == text)
                    return true;
            }
        }
    }

    return false;
}
