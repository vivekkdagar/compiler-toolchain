#include <iostream>
#include <vector>
#include <sstream>
#include "include/LeftFactorer.h"

using std::string;
using std::vector;

using namespace std;


int main() {
    rule obj;
    obj.lhs = 'S';
    obj.rhs = {"aS", "Fs", "b", "aA"};
    LeftFactor g(obj);
    g.setProduction(obj);
    g.factor();
    cout << g.getLeftFactoredCfg();
    return 0;
}
