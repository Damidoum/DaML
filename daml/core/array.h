#pragma once
#include <vector>

template <typename T>
class Array
{
public:
    Array() = default;
    Array(std::vector<int> shape);

    ~Array() = default;

    int dim();
    std::vector<int> shape() { return m_Shape; }

private:
    std::vector<int> m_Shape = {0};
    T *data = nullptr;
    T *buffer = nullptr;
    size_t m_BufferSize = 0;
};

template <typename T>
Array<T>::Array(std::vector<int> shape)
{
    Array();
    m_Shape = shape;
}

template <typename T>
int Array<T>::dim()
{
    int arrayDim = 1;
    for (int i = 0; i < m_Shape.size(); i++)
    {
        arrayDim *= m_Shape[i];
    }
    return arrayDim;
}

// opertor == overload
template <typename T>
bool operator==(Array<T> &a, Array<T> &b)
{
    if (a.shape() != b.shape())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < a.dim(); i++)
        {
            if (a->data[i] != b->data[i])
            {
                return false;
            }
        }
    }
};