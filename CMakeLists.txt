cmake_minimum_required(VERSION 3.1)
project(newton)
add_library(
    libnewton
    STATIC
    ./src/classes/newton.cxx
    )
add_executable(${PROJECT_NAME} ./src/root/main.cc)
target_link_libraries(${PROJECT_NAME} libnewton)