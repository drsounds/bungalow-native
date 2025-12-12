//
// Created by Alexander Forselius on 2025-12-12.
//

#include "PySPElement.h"


PYBIND11_MODULE(cmake_example, m) {
	py::class_<space::SPElement>(py::module &m, "SPElement", py::dynamic_attr());
