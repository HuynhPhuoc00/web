#include <pybind11/pybind11.h>

int multiply(int a, int b) {
    return a * b;
}

PYBIND11_MODULE(my_module, m) {
    m.def("multiply", &multiply, "Hàm nhân hai số");
}
