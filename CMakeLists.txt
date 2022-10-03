cmake_minimum_required(VERSION 3.12)
project(telempy)

add_subdirectory(lib/telemetry)
add_subdirectory(lib/pybind11)

set(SOURCE_DIR "src/telemetry")
set(SOURCES "${SOURCE_DIR}/telemetry_bindings.cpp")

pybind11_add_module(telemetry ${SOURCES})
target_link_libraries(telemetry PRIVATE telemetry_core)
