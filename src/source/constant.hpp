#ifndef _CONSTANT_
#define _CONSTANT_
#include <string>
constexpr std::string_view LICENSE_TEXT{R"(
Copyright(C)<YEAR> <COPYRIGHT_HOLDER>.

Permission is hereby granted, free of charge,
to any person obtaining a copy of this software and associated documentation files (the “Software”),
to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE)"};

constexpr std::string_view CPACK_CODE{R"(
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VENDOR "Cool \"Company\"")
include(CPack))"};

constexpr std::string_view GITIGNORE_CODE{
    R"(
CMakeLists.txt.user
CMakeCache.txt
CMakeFiles
CMakeScripts
Testing
Makefile
cmake_install.cmake
install_manifest.txt
compile_commands.json
CTestTestfile.cmake
_deps
build
)"};

constexpr std::string_view CMAKE_CODE{
    R"(
#Auto Genrated CMake file by aura CLI
#Copyright 2023 Vishal Ahirwar. #replace with your copyright notice.
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
include_directories(./src/includes)
#@find)"};

std::string MAIN_CODE{
    R"(
//Auto Genrated C++ file by aura CLI
//Copyright 2023 Vishal Ahirwar //replace it with your copyright notice!
#include<iostream>
int main(int argc,char*argv[])
{
    std::cout<<"@";
    return 0;
};

)"};

constexpr std::string_view TEST_CODE{R"(
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)
FetchContent_MakeAvailable(Catch2)
add_executable(tests ./tests/main.cc)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
)"};
constexpr std::string_view TEST_CXX_CODE{R"(
#include <catch2/catch_test_macros.hpp>

unsigned int Factorial(unsigned int number)
{
    return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
    REQUIRE(Factorial(1) == 1);
    REQUIRE(Factorial(2) == 2);
    REQUIRE(Factorial(5) == 120);
})"};
constexpr std::string_view CONAN_CODE{R"([requires]

[generators]
CMakeDeps
CMakeToolchain
[layout]
cmake_layout
)"};
#ifdef WIN32
constexpr std::string_view COMPILER_URL_64BIT{"https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-msvcrt-r2/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r2.7z"};
constexpr std::string_view COMPILER_URL_32BIT{"https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.1-12.0.0-msvcrt-r2/winlibs-i686-posix-dwarf-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r2.7z"};

constexpr std::string_view CMAKE_URL_64BIT{"https://github.com/Kitware/CMake/releases/download/v3.31.2/cmake-3.31.2-windows-x86_64.zip"};
constexpr std::string_view CMAKE_URL_32BIT{"https://github.com/Kitware/CMake/releases/download/v3.31.2/cmake-3.31.2-windows-i386.zip"};

constexpr std::string_view UPDATER_URL{"https://github.com/vishal-ahirwar/aura/releases/latest/download/utool.exe"};

constexpr std::string_view CONAN_URL_64BIT{"https://github.com/conan-io/conan/releases/download/2.11.0/conan-2.11.0-windows-x86_64.zip"};
constexpr std::string_view CONAN_URL_32BIT{"https://github.com/conan-io/conan/releases/download/2.11.0/conan-2.11.0-windows-i686.zip"};
#else
constexpr std::string_view UPDATER_URL{"https://github.com/vishal-ahirwar/aura/releases/latest/download/utool"
};
#endif
#endif
