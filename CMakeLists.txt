cmake_minimum_required(VERSION 3.1)
project(newton)
set(CMAKE_CXX_STANDARD 20)
add_executable(${PROJECT_NAME} ./src/main.cc ./src/source/app.cc ./src/source/newton.cc)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

