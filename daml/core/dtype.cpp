#include <iostream>
#include "dtype.h"

Dtype::Dtype(Type type) : type_(type){
    switch (type_){
        case int32:
            typeSize_ = 4;
            break;
        case float32:
            typeSize_ = 4;
            break;
        case bool_:
            typeSize_ = 1;
            break;
        default:
            std::cout << "Error: invalid type" << std::endl;
            break;
    }
}

Dtype::Dtype(char id)
{
    switch (id)
    {
    case 'i':
        type_ = int32;
        typeSize_ = 4;
        break;
    case 'f':
        type_ = float32;
        typeSize_ = 4;
        break;
    case 'b':
        type_ = bool_;
        typeSize_ = 1;
        break;
    }
}

    bool
    operator==(const Dtype &dtype1, const Dtype &dtype2)
{
    if (dtype1.typeSize_ == dtype2.typeSize_)
        return true;
    else
        return false;
}
