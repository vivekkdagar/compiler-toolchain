#include "include/LeftRecursion.h"

using namespace std;


int main() {
    rule obj;
    obj.lhs = 'S';
    obj.rhs = {"S1", "S2", "S3", "Bd", "Be", "Bf"};
    LeftRecursion g(obj);
    g.convert();
    cout << g.getRightRecursiveCfg();
    return 0;
}
