#include <iostream>
#include "core/array.h"

using namespace std;

int main(int, char **)
{
    vector<int> shape = {3, 2, 3};
    Array<int> a = Array<int>(shape);
    Array<int> c({3, 2, 3});
    Array<int> b;
    cout << (a == c) << endl;
    return 0;
}
