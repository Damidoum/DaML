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
    Array() = default;  // default constructor
    ~Array() = default; // default destructor

    template <typename T>
    Array(T val, std::vector<int> shape); // constructor with val and shape (same value for all elements)

    template <typename T>
    Array(std::initializer_list<T> list, std::vector<int> shape); // constructor with list and shape

private:
    void *offset = nullptr;    // offset of the array
    std::vector<int> shape_;   // shape of the array
    std::vector<int> strides_; // strides of the array
    int size_ = 0;             // size of the array in bytes
    Dtype dtype_;              // data type of the array
    Buffer buffer_;            // buffer of the array

    int computeSize();
    void computeStrides();
};

template <typename T>
Array::Array(T val, std::vector<int> shape)
{
    Array();
    shape_.assign(shape.begin(), shape.end());  // need to optimize this
    computeStrides();                           // need to optimize this
    dtype_ = Dtype(sizeof(T));                  // converte type to Dtype
    size_ = computeSize();                      // compute the size of the array
    buffer_.allocate(size_ * dtype_.typeSize_); // allocate memory for the array
    offset = buffer_.ptr_;                      // set the offset to the beginning of the array

    // initialize the array with val
    for (int i = 0; i < size_; i++)
    {
        *((T *)offset + i) = val;
    }
}

template <typename T>
Array::Array(std::initializer_list<T> list, std::vector<int> shape)
{
    Array();
    shape_.assign(shape.begin(), shape.end());  // need to optimize this
    computeStrides();                           // need to optimize this
    dtype_ = Dtype(sizeof(T));                  // converte type to Dtype
    size_ = computeSize();                      // compute the size of the array
    buffer_.allocate(size_ * dtype_.typeSize_); // allocate memory for the array
    offset = buffer_.ptr_;                      // set the offset to the beginning of the array

    // initialize the array with list
    for (int i = 0; i < size_; i++)
    {
        *((T *)offset + i) = *(list.begin() + i);
    }
}