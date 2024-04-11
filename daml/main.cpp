#include <iostream>
#include <vector>
#include "core/arraylib.h"

int main(int, char **)
{
    std::vector<int> shape = {3, 256, 256};
    Array array1(1, shape);
    Array array2(2, shape);
    return 0;
}
