cmake_minimum_required(VERSION 3.6)
project(ccli VERSION 2.1.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")
set(COMPANY "Vishal ahirwar")
string(TIMESTAMP CURRENT_YEAR "%Y")
set(COPYRIGHT "Copyright(c) ${CURRENT_YEAR} Vishal Ahirwar and all Contributors. All rights reserved.")
configure_file(ccliConfig.h.in ccliConfig.h)
add_executable(${PROJECT_NAME} 
    src/main.cc
    src/source/app.cc
    src/source/ccli.cc)

target_include_directories(${PROJECT_NAME} PUBLIC 
    src/includes
    ${PROJECT_BINARY_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
include(CPack)
