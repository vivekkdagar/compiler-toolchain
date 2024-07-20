//
// Created by vivekdagar on 20/7/24.
//

#ifndef CFG_H
#define CFG_H

#include "Grammar.h"
#include <vector>

using std::string, std::vector;

struct rule {
    char lhs;
    vector<string> rhs;
};

class CFG : public Grammar {
    vector<rule> prods;

public:
    void write(std::ostream &os) const override;

    void read(std::istream &is) override;

    void addRule(char lhs, const std::string &text);

    bool locate(char lhs, const std::string &text);

    [[nodiscard]] const vector<rule> &toVector() const {
        return prods;
    }
};


#endif //CFG_H
