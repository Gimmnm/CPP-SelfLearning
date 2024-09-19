cmake_minimum_required(VERSION 3.15)
project(list LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Listlib)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Listlib)