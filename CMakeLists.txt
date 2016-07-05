cmake_minimum_required(VERSION 3.3)
project(AlgC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES PreparaçãoExame/t.c)
#set(SOURCE_FILES Aula1/Ex1/main.cpp)
add_executable(AlgC ${SOURCE_FILES})