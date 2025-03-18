cmake_minimum_required(VERSION 3.31)
project(Pattern)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(Pattern main.cpp)
add_executable(Prototype prototype.cpp)
add_executable(Singleton singleton.cpp)
add_executable(Factory factory.cpp)
add_executable(Builder builder.cpp)
add_executable(Adapter adapter.cpp)
