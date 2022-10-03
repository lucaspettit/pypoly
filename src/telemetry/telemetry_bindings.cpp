#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../../lib/telemetry/include/telemetryReader.h"

namespace py = pybind11;

PYBIND11_MODULE(telemetryReader, m) {
    py::options options;
    options.disable_function_signatures();

    m.doc() = "Telemetry reader for GT7";

    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO;
    #else
        m.attr("__version__") = "dev";
    #endif
}