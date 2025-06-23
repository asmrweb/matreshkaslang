cmake_minimum_required(VERSION 3.14)
project(MatreshkaScript)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

file(GLOB SOURCES "src/*.cpp")
add_executable(matreshka ${SOURCES})

target_link_libraries(matreshka ${LLVM_LIBRARIES} ${LLVM_CORE} ${LLVM_SUPPORT})