cmake_minimum_required(VERSION 3.1)
project(newton)

add_executable(${PROJECT_NAME} ./src/newton/main.cc ./src/source/app.cc ./src/source/newton.cc ./src/source/version.cc)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

