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

void App::createNewProject(const char* argv[])
{
	clock_t start = clock(), end = 0;

	printf("%sCreating directory ....\n%s",GREEN,WHITE);

	std::string cmdString{};
	createDir(argv[2]);
	printf("%sGenerating Code for main.c and CMakeLists.txt ....\n%s",GREEN,WHITE);

	generateCppTemplateFile(argv[2]);
	generateCmakeFile(argv[2]);
	generateNewtonFile(projectName);
	generateGitIgnoreFile();


	end = clock();

	printf("%sElapsed Time : %8.2fms\nWith great power comes great responsibility\n%s", YELLOW, difftime(end, start),WHITE);
};

void App::compile()
{
	printf("%sCompile Process has been started ....\n%s",BLUE,WHITE);
#ifdef WIN32
	if (!system("cmake -S . -B build -G \"MinGW Makefiles\" "))
	{
		if(!system("mingw32-make -C build"))//if there is any kind of error then don't clear the terminal
		system("cls");
	}
	else
	{
		printf("%s\n[error] Make Sure You are in Your Project's Directory!\n%s",RED,WHITE);
	};
#else
	if (!system("cmake -S . -B build"))
	{
		if(!system("make -C build/"))//if there is any kind of error then don't clear the terminal
		system("clear");
	}
	else
	{
		printf("%s\n[error] Make Sure You are in Your Project's Directory!\n%s",RED,WHITE);
	};
#endif

};

void App::run()
{
	std::string output{};
	readNewtonFile(output);
	projectName = output;

	std::string run{};
	//printf("%s%s: \n%s", YELLOW, projectName.c_str(),WHITE);
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
		printf("%s\n[error] Maybe You should Compile First Before run or You have Permission to execute program!\n%s",RED,WHITE);
	};
}

void App::build()
{

	this->compile();
	this->run();
}

void App::setup()
{
	printf("%sAdding newton CLI to path...%s\n", YELLOW, WHITE);

	printf("\n%sthis feature is currently in development or maybe your CLI is not up to date!\n%s",CYAN,WHITE);
};

void App::generateNewtonFile(const std::string& path)
{
	std::string newFileName{ path };
	newFileName += "/setting.nn";
	std::ofstream file(newFileName.c_str(), std::ios::out);
	if (file.is_open())
	{
		time_t now{ time(NULL) };
		const char* dateTime{ ctime(&now) };

		file << projectName << "\n";
		file << "Project created on " <<dateTime<< "\n";
		printf("%sProject Creation date : %s%s", YELLOW, dateTime, WHITE);
		file << "Note: Please don't remove or edit this file!\n";
		file.close();
	}
	else
	{
		printf("%ssomething went wrong!\n%s",RED,WHITE);
	}
}

void App::readNewtonFile(std::string& output)
{
	std::ifstream file("setting.nn");
	if (file.is_open())
	{
		std::getline(file, output);
		std::string dateTime{};
		std::getline(file, dateTime);
		printf("%s[%s: %s]%s\n\n", YELLOW,output.c_str() ,dateTime.c_str(), WHITE);
		file.close();
	}
	else
	{
		printf("%snewton file setting.nn doesn't exist!\n%s",RED,WHITE);
	};
}

void App::createDir(const char* argv)
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
	else {
		printf("%sfailed to create dir error!%s",RED,WHITE);
		exit(0);
	}

};

void App::generateCppTemplateFile(const char* argv)
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
//Copyright 2023 Vishal Ahirwar //replace it with yout copyright notice!
#include<iostream>
int main(int argc,char*argv[])
{
    std::cout<<"@";
    return 0;
};

)" };
		auto pos = mainCode.find("@");
		std::string str{ std::string("Hello, ") + projectName + std::string("\\nhappy coding journey :)\\n") };
		mainCode.insert(pos + 1, str);
		file << mainCode;
		file.close();
	};
}

void App::generateCmakeFile(const char* argv)
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
set(CMAKE_CXX_STANDARD 17))" };
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

)" };
		file << cmakeCode;

		file.close();
	};
}
;
