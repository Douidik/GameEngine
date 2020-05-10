cmake_minimum_required(VERSION 3.16)
project(engine)
project(sandbox)
#project use CPP 20
set(CMAKE_CXX_STANDARD 20)

#Setup new output directories for binaries and libraries in root/bin & root/lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(src/engine/)
add_subdirectory(src/sandbox/)

#We link the sandbox application with the engine dll
target_link_libraries(sandbox engine)