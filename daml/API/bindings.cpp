#include <pybind11/pybind11.h>
#include "../core/arraylib.h"

namespace py = pybind11;

PYBIND11_MODULE(daml, m)
{
    py::class_<Array>(m, "Array")
        .def(py::init<int>())
        .def(py::init<float>())
        .def("add", &Array::add)
        .def("sub", &Array::sub)
        .def("multiply", &Array::multiply)
        .def("divide", &Array::divide)
}