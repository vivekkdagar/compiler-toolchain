//
// Created by vivekdagar on 20/7/24.
//

#ifndef PROPAGATOR_H
#define PROPAGATOR_H

#include <unordered_set>
#include "../grammar/CFG.h"

std::unordered_set<char> propagate(const CFG &cfg);

char free(std::unordered_set<char> obj);


#endif //PROPAGATOR_H
