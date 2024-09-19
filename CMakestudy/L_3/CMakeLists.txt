add_subdirectory(add)

include_directories(./lib)

link_directories(/Users/gzh/Documents/Learning/Zju/数据结构与算法/CPP-SelfLearning/CMakestudy/L_3/lib)

add_executable(study3 main.cpp)
target_link_libraries(study3 add_static)
