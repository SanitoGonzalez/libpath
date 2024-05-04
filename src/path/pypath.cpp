#include <path/navigator.hpp>
#include <pybind11/pybind11.h>

namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

PYBIND11_MODULE(libpath, m) {
    py::class_<path::Point>(m, "Point")
        .def(py::init<size_t, size_t>())
        .def_readonly("r", &path::Point::r)
        .def_readonly("c", &path::Point::c)
        .def("__eq__", &path::Point::operator==);

    // py::class_<path::Grid>(m, "Grid")
    //     .def(py::init<std::vector<int>, size_t, size_t>())
    //     // .def("__call__", py::overload_cast<const path::Point>)
    //     .def("get_neighbors", &path::Grid::get_neighbors);
}
