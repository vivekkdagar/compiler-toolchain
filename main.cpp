#include <iostream>
#include "include/analysis/LeftFactor.h"
#include "include/analysis/LeftRecursion.h"

using namespace std;

int main() {
    CFG obj;
    cin >> obj;
    obj.addRule('F', "#");

    LeftRecursion src(obj);
    src.convert();
    cout << src.output();
   // cout << obj.locate('F', "#");
}
