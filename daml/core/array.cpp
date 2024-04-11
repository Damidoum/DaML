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

Buffer::Buffer(size_t numberOfBytes)
{
    allocate(numberOfBytes);
}

Array::Array(const Array &other)
{
    shape_ = other.shape_;
    strides_ = other.strides_;
    size_ = other.size_;
    dtype_ = other.dtype_;
    buffer_ = Buffer(other.size_ * other.dtype_.typeSize_);
    offset_ = buffer_.ptr_;
    std::memcpy(buffer_.ptr_, other.buffer_.ptr_, other.size_ * other.dtype_.typeSize_);
}

Array::Array(std::vector<int> shape, Dtype dtype)
{
    shape_ = shape;
    dtype_ = dtype;
    computeStrides();
    size_ = computeSize();
    buffer_ = Buffer(size_ * dtype_.typeSize_);
    offset_ = buffer_.ptr_;
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

void Array::computeStrides()
{
    strides_.assign(shape_.size(), 1);
    for (int i = shape_.size() - 2; i >= 0; i--)
    {
        strides_[i] = strides_[i + 1] * shape_[i + 1];
    }
}