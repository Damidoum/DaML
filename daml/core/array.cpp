#include <iostream>
#include <cstdlib>
#include "array.h"

void Buffer::allocate(size_t numberOfBytes)
{
    if (numberOfBytes <= numberOfBytes_)
    {
        std::cout << "Enought memory allocated" << std::endl;
    }
    else
    {
        void *tempPtr = nullptr;
        tempPtr = malloc(numberOfBytes);
        if (tempPtr == nullptr)
            std::cout << "Error: could not allocate memory" << std::endl;
        else
        {
            std::memcpy(tempPtr, ptr_, numberOfBytes_);
            free(ptr_);
            ptr_ = tempPtr;
            numberOfBytes_ = numberOfBytes;
        }
    }
}

int Array::computeSize()
{
    int size = 1;
    for (int i = 0; i < shape_.size(); i++)
    {
        size *= shape_[i];
    }
    return size;
}
