#include "include/LeftRecursion.h"

using namespace std;


int main() {
    rule obj;
    obj.lhs = 'S';
    obj.rhs = {"S12","bD"};
    LeftRecursion g(obj);
    g.convert();
    cout << g.getRightRecursiveCfg();
    return 0;
}
