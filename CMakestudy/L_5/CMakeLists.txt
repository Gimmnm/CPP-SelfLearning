add_subdirectory(add)
add_subdirectory(sub)
add_subdirectory(cal)
add_subdirectory(common)

add_executable(study5 main.cpp)
target_link_libraries(study5 cal)

