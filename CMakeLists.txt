cmake_minimum_required(VERSION 3.12)
project(project2)

set(CMAKE_CXX_STANDARD 11)

add_executable(project2 main.cpp Passenger.cpp Passenger.h main.cpp Simulator.cpp Simulator.h Event.cpp Event.h)