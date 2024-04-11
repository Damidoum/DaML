#pragma once
#include <vector>
#include "dtype.h"

struct Buffer
{
    void *ptr_ = nullptr;
    size_t numberOfBytes_ = 0;

    Buffer() = default;
    Buffer(size_t numberOfBytes);
    ~Buffer() = default;

    void allocate(size_t numberOfBytes);
};

class Array
{
public:
    Array() = default;  // default constructor
    ~Array() = default; // default destructor

    template <typename T>
    Array(T val, std::vector<int> &shape); // constructor with val and shape (same value for all elements)

    template <typename T>
    Array(std::initializer_list<T> list, std::vector<int> &shape); // constructor with list and shape

    Array(const Array &other);                  // copy constructor
    Array(std::vector<int> shape, Dtype dtype); // constructor with shape and dtype

    std::vector<int> shape() { return shape_; }
    std::vector<int> getStrides() { return strides_; }
    int size() { return size_; }
    Dtype dtype() { return dtype_; }

    // operations
    bool checkOperatorCompatibility(Array &array1, Array &array2);
    Array add(Array &other, bool inplace = false);
    Array sub(Array &other, bool inplace = false);
    Array multiply(Array &other, bool inplace = false);
    Array divide(Array &other, bool inplace = false);

private:
    void *offset_ = nullptr;   // offset of the array
    std::vector<int> shape_;   // shape of the array
    std::vector<int> strides_; // strides of the array
    int size_ = 0;             // size of the array in bytes
    Dtype dtype_;              // data type of the array
    Buffer buffer_;            // buffer of the array

    // getters
    template <typename T>
    T *data() { return (T *)buffer_.ptr_; }

    int computeSize();
    void computeStrides();

    // generic operation
    template <typename T, typename Op>
    Array genericOperator(Op op, Array &other, bool inplace = false);
    template <typename Op>
    Array wellTypedGenericOperator(Op op, Array &other, bool inplace = false);
};

template <typename T>
Array::Array(T val, std::vector<int> &shape)
{
    shape_.assign(shape.begin(), shape.end());  // need to optimize this
    computeStrides();                           // need to optimize this
    dtype_ = Dtype(typeid(T).name()[0]);        // converte type to Dtype
    size_ = computeSize();                      // compute the size of the array
    buffer_.allocate(size_ * dtype_.typeSize_); // allocate memory for the array
    offset_ = buffer_.ptr_;                     // set the offset to the beginning of the array

    T *bufferPtr = data<T>();

    // initialize the array with val
    for (int i = 0; i < size_; i++)
    {
        *(bufferPtr + i) = val;
    }
}

template <typename T>
Array::Array(std::initializer_list<T> list, std::vector<int> &shape)
{
    shape_.assign(shape.begin(), shape.end());  // need to optimize this
    computeStrides();                           // need to optimize this
    dtype_ = Dtype(typeid(T).name()[0]);        // converte type to Dtype
    size_ = computeSize();                      // compute the size of the array
    buffer_.allocate(size_ * dtype_.typeSize_); // allocate memory for the array
    offset_ = buffer_.ptr_;                     // set the offset to the beginning of the array

    if (list.size() != size_)
    {
        std::cout << "Error: incompatible size" << std::endl;
        return;
    }

    T *bufferPtr = data<T>();

    // initialize the array with list
    for (int i = 0; i < size_; i++)
    {
        *(bufferPtr + i) = *(list.begin() + i);
    }
}

template <typename T, typename Op>
Array Array::genericOperator(Op op, Array &other, bool inplace /* = false */)
{
    if (!checkOperatorCompatibility(*this, other))
    {
        return *this;
    }
    else
    {
        T *bufferPtr = data<T>();
        T *otherBufferPtr = other.data<T>();
        if (inplace)
        {
            for (int i = 0; i < size_; i++)
            {
                bufferPtr[i] = op(bufferPtr[i], otherBufferPtr[i]);
            }
            return *this;
        }
        else
        {
            Array output = Array(shape_, dtype_);
            T *outputBufferPtr = output.data<T>();
            for (int i = 0; i < size_; i++)
            {
                outputBufferPtr[i] = op(bufferPtr[i], otherBufferPtr[i]);
            }
            return output;
        }
    }
}

template <typename Op>
Array Array::wellTypedGenericOperator(Op op, Array &other, bool inplace /* = false*/)
{
    switch (dtype_.type_)
    {
    case Type::int32:
        return genericOperator<int>(op, other, inplace);
        break;
    case Type::float32:
        return genericOperator<float>(op, other, inplace);
        break;
    case Type::bool_:
        return genericOperator<bool>(op, other, inplace);
        break;
    default:
        std::cout << "Error: invalid type" << std::endl;
        break;
    }
}