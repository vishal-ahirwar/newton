
#Auto Genrated CMake file by aura CLI
#Copyright 2023 Vishal Ahirwar. #replace with your copyright notice.
cmake_minimum_required(VERSION 3.6...3.31)
project(hello_wworld VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
include_directories(./src/includes)
#@find
find_package(fmt REQUIRED)
set(SOURCE ./src/main.cc)#add your additional source file here!
add_executable(${PROJECT_NAME} ${SOURCE})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#@link
target_link_libraries(${PROJECT_NAME} fmt::fmt)
#Unit Testing CMake Section
find_package(Catch2)
add_executable(tests ./tests/main.cc)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
