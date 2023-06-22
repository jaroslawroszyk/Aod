cmake_minimum_required(VERSION 3.22)
project(MaxFlow)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_executable(maxflow src/main.cpp src/Graph.cpp )

target_compile_features(maxflow PRIVATE cxx_std_20)
target_link_libraries(maxflow stdc++)
