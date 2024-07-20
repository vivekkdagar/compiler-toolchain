//
// Created by vivekdagar on 20/7/24.
//

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>

// Grammar abstract class

class Grammar {
public:
    virtual ~Grammar() = default;

    // Pure virtual functions for reading and writing
    virtual void read(std::istream& is) = 0;
    virtual void write(std::ostream& os) const = 0;

    // Overloaded operators
    friend std::ostream& operator<<(std::ostream& os, const Grammar& grammar) {
        grammar.write(os);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Grammar& grammar) {
        grammar.read(is);
        return is;
    }
};

#endif //GRAMMAR_H
