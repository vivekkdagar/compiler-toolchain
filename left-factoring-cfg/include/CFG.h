//
// Created by vivekdagar on 01/05/24.
//

#ifndef LEFT_FACTORING_CFG_CFG_H
#define LEFT_FACTORING_CFG_CFG_H


// Production is: A -> AbC | CDD
// A is in lhs, AbC and CDD are two elements of vector rhs.

#include <string>
#include <vector>
#include <iostream>

using std::string, std::vector;

struct rule {
    char lhs;
    vector<string> rhs;
};

class CFG {
    vector<rule> prods;
public:

    friend std::ostream &operator<<(std::ostream &os, const CFG &obj) {

        for (auto &r: obj.prods) {
            os << r.lhs << " -> ";

            if (r.rhs.size() == 1) {
                os << r.rhs.at(0);
            } else {
                for (size_t j{0}; j < r.rhs.size(); ++j) {
                    os << r.rhs[j];
                    if (j not_eq r.rhs.size() - 1) // If not the last element
                        os << " | ";
                }
            }
            os << std::endl;
        }
        return os;
    }

    void addRule(char lhs, const std::string &text);
};


#endif //LEFT_FACTORING_CFG_CFG_H
