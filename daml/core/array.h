#pragma once
#include <vector>
#include "dtype.h"

struct Buffer
{
    void *ptr_ = nullptr;
    size_t numberOfBytes_ = 0;

    Buffer() = default;
    ~Buffer() = default;

    void allocate(size_t numberOfBytes);
};

class Array
{
public:
    Array() = default; // default constructor
    ~Array() = default; //default destructor

    template <typename T>
    Array(T val, std::vector<int> shape); // constructor with val and shape (same value for all elements)

private:
    void *offset = nullptr;    // offset of the array
    std::vector<int> shape_;   // shape of the array
    std::vector<int> strides_; // strides of the array
    int size_ = 0;             // size of the array in bytes
    Dtype dtype_;              // data type of the array
    Buffer buffer_;            // buffer of the array

    int computeSize();
};

template <typename T>
Array::Array(T val, std::vector<int> shape)
{
    Array();
    shape_.assign(shape.begin(), shape.end()); // need to optimize this
    strides_.assign(shape_.size(), 0);              // need to optimize this
    strides_[0] = 1;
    for (int i = 1; i < shape_.size(); i++)
    {
        strides_[i] = strides_[i - 1] * shape_[i - 1];
    }
    dtype_ = Dtype(sizeof(T));
    size_ = computeSize();
    buffer_.allocate(size_ * dtype_.typeSize_);
    offset = buffer_.ptr_;
}