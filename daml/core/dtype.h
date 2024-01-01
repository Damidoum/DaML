#pragma once
#include <string>

enum Type
{
    int32,
    float32,
    bool_,
}; // data types

struct Dtype
{
    Type type_ = int32; // type of the data
    int typeSize_ = 4;  // size of the type in bytes

    Dtype() = default;
    Dtype(Type type);
    Dtype(char id);

    ~Dtype() = default;
};


bool operator==(const Dtype &dtype1, const Dtype &dtype2);