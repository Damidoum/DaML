#include <iostream>
#include <vector>
#include "core/array.h"

using namespace std;

int main(int, char **)
{
    int a = 2;
    cout << "Hello, world !\n"
         << endl;
    std::vector<int> shape = {2, 3};
    Array test1;
    Array test = Array(1, shape);
    return 0;
}
