add_library(cal STATIC cal.cpp)
target_include_directories(cal PUBLIC ./)
target_link_libraries(cal PRIVATE add sub)