cmake_minimum_required(VERSION 3.16)
#project use CPP 20
set(CMAKE_CXX_STANDARD 20)

set(PRECOMPILED_HEADER_FILE EnginePCH.h)

#libraries
find_package(PkgConfig REQUIRED)

#glfw
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
#glew
pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
#opengl
pkg_search_module(OPENGL REQUIRED opengl)
#assimp
pkg_search_module(ASSIMP REQUIRED assimp)
include_directories(${ASSIMP_INCLUDE_DIRS})
#glm
pkg_search_module(GLM REQUIRED glm)
include_directories(${GLM_INCLUDE_DIRS})
#vendors
set(VENDOR_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/vendor/)
set(LIBRARIES ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${ASSIMP_LIBRARIES} ${GLM_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR}/src/engine/)
include_directories(${VENDOR_INCLUDE_DIRECTORIES})

file(GLOB_RECURSE ENGINE_SRC *.cpp)
file(GLOB_RECURSE ENGINE_HDR *.h)

add_library(engine SHARED ${ENGINE_SRC} ${ENGINE_HDR})
target_link_libraries(engine ${LIBRARIES})
target_precompile_headers(engine PUBLIC ${PRECOMPILED_HEADER_FILE})
