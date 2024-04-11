#include <iostream>
#include "array.h"
#include "operations.h"

bool Array::checkOperatorCompatibility(Array &array1, Array &array2)
{
    if (array1.shape_ != array2.shape_)
    {
        std::cout << "Error: incompatible shapes" << std::endl;
        return false;
    }
    else if (array1.dtype_ != array2.dtype_)
    {
        std::cout << "Error: incompatible dtypes" << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

Array Array::add(Array &other, bool inplace /* = false */)
{
    auto op = [](auto a, auto b)
    { return a + b; };
    return wellTypedGenericOperator(op, other, inplace);
}

Array Array::sub(Array &other, bool inplace /* = false */)
{
    auto op = [](auto a, auto b)
    { return a - b; };
    return wellTypedGenericOperator(op, other, inplace);
}

Array Array::multiply(Array &other, bool inplace /* = false */)
{
    auto op = [](auto a, auto b)
    { return a * b; };
    return wellTypedGenericOperator(op, other, inplace);
}

Array Array::divide(Array &other, bool inplace /* = false */)
{
    auto op = [](auto a, auto b)
    { return a / b; };
    return wellTypedGenericOperator(op, other, inplace);
}

/* --------------- Overload operators ------------------- */

Array operator+(Array &array1, Array &array2)
{
    Array output = array1.add(array2, false); // inplace = false
    return output;
}

Array operator-(Array &array1, Array &array2)
{
    Array output = array1.sub(array2, false); // inplace = false
    return output;
}

Array operator*(Array &array1, Array &array2)
{
    Array output = array1.multiply(array2, false); // inplace = false
    return output;
}

Array operator/(Array &array1, Array &array2)
{
    Array output = array1.divide(array2, false); // inplace = false
    return output;
}