cmake_minimum_required(VERSION 3.5)

project(minipbrt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minipbrt
  main.cpp
  minipbrt.cpp
  minipbrt.h
)
