cmake_minimum_required(VERSION 3.1)

project(Gaus)

set(SOURCE_EXE Gaus.c)
add_executable(main ${SOURCE_EXE})
target_link_libraries(main)
