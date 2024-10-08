#include "newton.hpp"
#include "colors.hpp"

#include <filesystem>
#include <ctime>
#include <string>
#include <stdio.h>
#include <fstream>

#ifndef WIN32
#include <unistd.h>
#endif

void App::setupUnitTestingFramework()
{
	std::ofstream file;
	file.open("CMakeLists.txt", std::ios::app);
	if (file.is_open())
	{
		std::string fetch_content{R"(
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/34ad51b.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
)"};

		file << fetch_content;
		file.close();
		printf("%s[Msg] : GTest added for unit testing :)%s\n", GREEN, WHITE);
	}
	else
	{
		printf("%s[error] : Failed to setup unit testing framework gtest :(%s\n", RED, WHITE);
	}
}

void App::createNewProject(const char *argv[], int argc)
{
	clock_t start = clock(), end = 0;

	printf("%sCreating directory ....\n%s", GREEN, WHITE);

	std::string cmdString{};
	createDir(argv[2]);
	printf("%sGenerating Code for main.c and CMakeLists.txt ....\n%s", GREEN, WHITE);

	generateCppTemplateFile(argv[2]);
	generateCmakeFile(argv[2]);
	generateNewtonFile(projectName);
	generateGitIgnoreFile();
	end = clock();

	printf("%sElapsed Time : %8.2fms\nWith great power comes great responsibility\n%s", YELLOW, difftime(end, start), WHITE);
};

void App::compile()
{
	printf("%sCompile Process has been started ....\n%s", BLUE, WHITE);
#ifdef WIN32
	if (!system("cmake -S . -B build -G \"MinGW Makefiles\" "))
	{
		if (!system("mingw32-make -C build")) // if there is any kind of error then don't clear the terminal
			printf("\n%sBUILD SUCCESSFULL%s\n", GREEN, WHITE);
		else
			printf("\n%sBUILD FAILED%s\n", RED, WHITE);
	}
	else
	{
		printf("%s\n[error] Make Sure You are in Your Project's Directory!\n%s", RED, WHITE);
	};
#else
	if (!system("cmake -S . -B build"))
	{
		if (!system("make -C build/")) // if there is any kind of error then don't clear the terminal
			printf("\n%sBUILD SUCCESSFULL%s\n", GREEN, WHITE);
		else
			printf("\n%sBUILD FAILED%s\n", RED, WHITE);
	}
	else
	{
		printf("%s\n[error] Make Sure You are in Your Project's Directory!\n%s", RED, WHITE);
	};
#endif
};

void App::run()
{
	std::string output{};
	readNewtonFile(output);
	projectName = output;

	std::string run{};
	// printf("%s%s: \n%s", YELLOW, projectName.c_str(),WHITE);
#ifdef WIN32
	run += ".\\build\\";
	run += projectName;
	run += ".exe";
#else
	run += "./build/";
	run += projectName;
#endif // WIN32

	if (system(run.c_str()))
	{
		printf("%s\n[error] Maybe You should Compile First Before run or You have Permission to execute program!\n%s", RED, WHITE);
	};
}

void App::build()
{

	this->compile();
	this->run();
}

void App::setup()
{
#ifdef WIN32
	printf("%s[Important] Make sure run this command with administrator privileges%s\n", CYAN, WHITE);
	printf("%sThis will install MinGW-13 Compiler and CMake 3.30,\nAre you sure you want to continue??[y/n] %s\n", YELLOW, WHITE);
	char input{};
	scanf("%c", &input);
	if (input == 'y' || input == 'Y')
	{
		printf("Installing Choco xd...\n");
		if (system("powershell -Command Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))") == 0)
		{
			if (system("choco install mingw") == 0)
			{
				if (system("choco install cmake") == 0)
				{
					printf("%sAll done%s", BLUE, WHITE);
				}
			};
		}
		else
		{
			printf("%sSomething went wrong!%s\n", RED, WHITE);
		}
	}
	else
	{
		printf("%sokie:)%s\n", CYAN, WHITE);
	};
#else
	printf("%sNot Availble on Linux :(%s\n", CYAN, WHITE);
#endif
};

void App::generateNewtonFile(const std::string &path)
{
	std::string newFileName{path};
	newFileName += "/setting.nn";
	std::ofstream file(newFileName.c_str(), std::ios::out);
	if (file.is_open())
	{
		time_t now{time(NULL)};
		const char *dateTime{ctime(&now)};

		file << projectName << "\n";
		file << "Project created on " << dateTime << "\n";
		printf("%sProject Creation date : %s%s", YELLOW, dateTime, WHITE);
		file << "Note: Please don't remove or edit this file!\n";
		file.close();
	}
	else
	{
		printf("%ssomething went wrong!\n%s", RED, WHITE);
	}
}

void App::readNewtonFile(std::string &output)
{
	std::ifstream file("setting.nn");
	if (file.is_open())
	{
		std::getline(file, output);
		std::string dateTime{};
		std::getline(file, dateTime);
		printf("%s[%s: %s]%s\n\n", YELLOW, output.c_str(), dateTime.c_str(), WHITE);
		file.close();
	}
	else
	{
		printf("%snewton file setting.nn doesn't exist!\n%s", RED, WHITE);
	};
}

void App::createDir(const char *argv)
{
	namespace fs = std::filesystem;
	std::string cmdString{};
	cmdString += argv;
	if (fs::create_directory(cmdString.c_str()))
	{
		cmdString += "/build";
		fs::create_directory(cmdString.c_str());
		auto pos = cmdString.find("/");
		cmdString.replace(pos + 1, cmdString.length() - pos, "src");

		fs::create_directory(cmdString.c_str());
		pos = cmdString.find("/");
		cmdString.replace(pos + 1, cmdString.length() - pos, "res");
		fs::create_directory(cmdString.c_str());
	}
	else
	{
		printf("%sfailed to create dir error!%s", RED, WHITE);
		exit(0);
	}
};

void App::generateCppTemplateFile(const char *argv)
{
	std::ofstream file;
	// const std::string stdStr{argv[2]};
	projectName = argv;
	file.open("./" + projectName + "/src/main.cc", std::ios::out);

	if (file.is_open())
	{
		std::string mainCode{
			R"(
//Auto Genrated C++ file by newton CLI
//Copyright 2023 Vishal Ahirwar //replace it with your copyright notice!
#include<iostream>
int main(int argc,char*argv[])
{
    std::cout<<"@";
    return 0;
};

)"};
		auto pos = mainCode.find("@");
		std::string str{std::string("Hello, ") + projectName + std::string("\\nhappy coding journey :)\\n")};
		mainCode.insert(pos + 1, str);
		file << mainCode;
		file.close();
	};
}

void App::generateCmakeFile(const char *argv)
{
	std::ofstream file;
	file.open("./" + projectName + "/CMakeLists.txt", std::ios::out);
	if (file.is_open())
	{
		const std::string cmakeCode{
			R"(
#Auto Genrated CMake file by newton CLI
#Copyright 2023 Vishal Ahirwar. #replace with your copyright notice.
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17))
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")"};
		file << cmakeCode << "\n";
		file << "project(" << argv << ")\n";
		file << "set(SOURCE ./src/main.cc)#add your additional source file here!\n";
		/*
		set(SOURCE ./src/main.cc ./src/player.cc ./src/person.cc)
		add_executable(${PROJECT_NAME} ${SOURCE})*/
		file << "add_executable(${PROJECT_NAME} ${SOURCE})\n";
		file << "install(TARGETS ${PROJECT_NAME} DESTINATION bin)\n";

		file.close();
	};
}

void App::generateGitIgnoreFile()
{
	std::ofstream file;
	file.open("./" + projectName + "/.gitignore", std::ios::out);
	if (file.is_open())
	{
		const std::string cmakeCode{
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

)"};
		file << cmakeCode;

		file.close();
	};
};

void App::generateLicenceFile()
{
	const std::string text{R"(
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

	std::ofstream out;
	out.open("License.txt", std::ios_base::out);
	if (!out.is_open())
	{
		printf("%s[Error]Failed to Generate License.txt, You may need to create License.txt by yourself :)%s", RED, WHITE);
		return;
	};
	out << text;
	out.close();
};

void App::createInstaller()
{
	std::ofstream file;
	file.open("CMakeLists.txt", std::ios::app);
	if (file.is_open())
	{
		std::string out{R"(
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VENDOR "Cool \"Company\"")
include(CPack))"};
		file << out;
		file.close();
		generateLicenceFile();
		if (system("cd build && cpack"))
			printf("%s[Msg]CPack added to cmake run 'cpack' command from build directory to build a installer :)%s\n", GREEN, WHITE);
	}
	else
	{
		printf("%s[Msg]Something went wrong :(%s\n", RED, WHITE);
	}
};

void App::gTest()
{
	setupUnitTestingFramework();
	build();
};
