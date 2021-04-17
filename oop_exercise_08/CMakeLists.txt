cmake_minimum_required(VERSION 3.0)

set(NAME oop_exercise_08)
file(GLOB_RECURSE SOURCE src/*.cpp)

project(${NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -lpthread")

add_executable(${NAME} ${SOURCE})
