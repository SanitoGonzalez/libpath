#include <path/navigator.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(libpath, m) {
    using namespace path;

    py::class_<Point>(m, "Point")
        .def(py::init<size_t, size_t>())
        .def_readonly("r", &Point::r)
        .def_readonly("c", &Point::c)
        .def("__eq__", &Point::operator==)
        .def("__repr__", &Point::to_string);

    py::class_<Grid>(m, "Grid")
        .def(py::init<const std::vector<int>&, size_t, size_t>())
        .def_readonly("rows", &Grid::rows)
        .def_readonly("cols", &Grid::cols)
        .def("at", &Grid::at);
    // .def("get_neighbors", &path::Grid::get_neighbors);

    py::class_<Navigator>(m, "Navigator")
        .def_static("navigate_astar", &Navigator::navigate_astar);
}
