cmake_minimum_required(VERSION 3.16)
#project use CPP 20
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/src/engine/)

file(GLOB_RECURSE SANDBOX_SRC *.cpp)
file(GLOB_RECURSE SANDBOX_HDR *.h)

add_executable(sandbox ${SANDBOX_SRC} ${SANDBOX_HDR})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")