cmake_minimum_required(VERSION 3.0)
project(pypoly)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/telemetry)
add_subdirectory(lib/pybind11)

set(SOURCE_DIR "src/telemetry")
set(SOURCES "${SOURCE_DIR}/telemetry_bindings.cpp")

pybind11_add_module(telemetry_bindings ${SOURCES})
target_link_libraries(telemetry_bindings PRIVATE telemetryReader)
