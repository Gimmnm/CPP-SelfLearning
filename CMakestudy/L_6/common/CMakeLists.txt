add_library(common_obj OBJECT common.cpp)
add_library(common STATIC $<TARGET_OBJECTS:common_obj>)
target_include_directories(common PUBLIC ./)