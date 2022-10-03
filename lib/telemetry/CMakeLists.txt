cmake_minimum_required(VERSION 3.12)

# The `cmake_minimum_required(VERSION 3.12...3.22)` syntax does not work with
# some versions of VS that have a patched CMake 3.11. This forces us to emulate
# the behavior using the following workaround:
if(${CMAKE_VERSION} VERSION_LESS 3.22)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.22)
endif()

# Prevent indefinit recursion 
if(DEFINED TELEMETRY_MASTER_PROJECT)
    return()
endif()

# Extract project version from source
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/include/utils/common.h"
     telemetry_version_defines REGEX "#define TELEMETRY_VERSION_(MAJOR|MINOR|PATCH) ")

foreach(ver ${telemetry_version_defines})
  if(ver MATCHES [[#define TELEMETRY_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$]])
    set(TELEMETRY_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}")
  endif()
endforeach()

if(TELEMETRY_VERSION_PATCH MATCHES [[\.([a-zA-Z0-9]+)$]])
  set(TELEMETRY_VERSION_TYPE "${CMAKE_MATCH_1}")
endif()
string(REGEX MATCH "^[0-9]+" TELEMETRY_VERSION_PATCH "${TELEMETRY_VERSION_PATCH}")

project(Telemetry)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(TELEMETRY_MASTER_PROJECT ON)
set(MODELS_LIB 
    include/models/bounds.h 
    source/models/bounds.cpp
    include/models/flags.h
    source/models/flags.cpp
    include/models/gearRatios.h
    source/models/gearRatios.cpp
    include/models/packet.h
    source/models/packet.cpp
    include/models/vector.h
    source/models/vector.cpp
    include/models/wheels.h
    source/models/wheels.cpp)
set(READER_LIB
    include/reader/packetReader.h
    source/reader/packetReader.cpp)
set(SECURITY_LIB
    include/security/cipher.h
    source/security/cipher.cpp
    include/security/salsa20.h
    source/security/salsa20.cpp)
set(UTILS_LIB
    include/utils/debug.h
    source/utils/debug.cpp
    include/utils/system.h
    source/utils/system.cpp)
set(TELEMETRY_LIB
    include/telemetryReader.h
    source/telemetryReader.cpp)

list(TRANSFORM MODELS_LIB PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM READER_LIB PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM SECURITY_LIB PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM UTILS_LIB PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
list(TRANSFORM TELEMETRY_LIB PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

add_library(telemetry_core SHARED ${MODELS_LIB} ${READER_LIB} ${SECURITY_LIB} ${UTILS_LIB} ${TELEMETRY_LIB})
target_include_directories(telemetry_core PUBLIC "$CMAKE_CURRENT_SOURCE_DIR/include")
#add_executable(main main.cpp)
#target_link_libraries(main telemetry)