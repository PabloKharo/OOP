cmake_minimum_required(VERSION 3.0)

set(NAME oop_exercise_01)
file(GLOB_RECURSE SOURCE src/*.cpp)

project(${NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

add_executable(${NAME} ${SOURCE})
