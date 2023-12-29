#pragma once
#include <string>

struct Dtype
{
    /* removing typeName for the moment
    char *typeName_ = "int32"; // name of the type
    */

    int typeSize_ = 4; // size of the type in bytes

    Dtype() = default;
    Dtype(int typeSize) : typeSize_(typeSize) {}
};