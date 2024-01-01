#include <iostream>
#include <vector>
#include "core/arraylib.h"

int main(int, char **)
{
    Array array1({1, 2, 3, 4}, {1, 4});
    Array array2({2, 1, 32, 5}, {1, 4});
    Array array3 = array1 + array2;
    Array array4 = array1 * array2;
    Array array5 = array1 - array2;
    Array array6 = array1 / array2;
    return 0;
}
