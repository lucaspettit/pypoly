cmake_minimum_required(VERSION 3.0)
project(Telemetry)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(telemetryReader STATIC telemetryReader.cpp)
target_include_directories(telemetryReader PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# Test setup
# add_executable(test_cipher_decrypt tests/test_cipher_decrypt.cpp)
# target_include_directories(test_cipher_decrypt PUBLIC ../catch2)
# target_link_libraries(test_cipher_decrypt PUBLIC telemetry_core)
