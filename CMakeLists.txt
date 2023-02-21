cmake_minimum_required(VERSION 3.24)
project(Client_Server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.74 REQUIRED)

add_subdirectory("Client(Program1)")
add_subdirectory("Server(Program2)")
