#include "../includes/newton.hpp"
#include<filesystem>

void App::createNewProject(const char* argv[])
{
	clock_t start = clock(), end = 0;

	printf("Creating directory ....\n");

	std::string cmdString{};
	createDir(argv[2]);
	printf("Generating Code for main.c and CMakeLists.txt ....\n");

	generateCppTemplateFile(argv[2]);
	generateCmakeFile(argv[2]);
	generateNewtonFile(projectName);
	end = clock();

	printf("Elapsed Time : %8.2fms\nHappy Coding...:)\n", difftime(end, start));
};

void App::compile()
{
	printf("[newton] Compile Process has been started ....\n");
	if (!system("cmake -S . -B build"))
	{
		system("make -C build/");
	}
	else
	{
		printf("\n[error] Make Sure You are in Your Project's Directory!\n");
	};
};

void App::run()
{
	std::string output{};
	readNewtonFile(output);
	projectName = output;
	std::cout << projectName << "\n";
	std::string run{};
	run += "./build/";
	run += projectName;
	if (system(run.c_str()))
	{
		std::cout << run << "\n";
		printf("\n[error] Maybe You should Compile First Before run or You have Permission to execute program!\n");
	};
};

void App::generateNewtonFile(const std::string& path)
{
	std::string newFileName{ path };
	newFileName += "/setting.nn";
	std::ofstream file(newFileName.c_str(), std::ios::out);
	if (file.is_open())
	{

		file << projectName << "\n";
		file << "Project created at : " << __DATE__ << "\n";
		file << "Note: Please don't remove or edit this file!\n";
		file.close();
	}
	else
	{
		printf("something went wrong!\n");
	}
}
void App::readNewtonFile(std::string& output)
{
	std::ifstream file("setting.nn");
	if (file.is_open())
	{
		file >> output;
		file.close();
	}
	else
	{
		printf("newton file setting.nn doesn't exist!\n");
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
		puts("error!");
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
#Auto Genrated C++ file by newton CLI
#Copyright2023 Vishal Ahirwar. #replace with your copyright notice.
cmake_minimum_required(VERSION 3.1)
)" };
		file << cmakeCode << "\n";
		file << "project(" << argv << ")\n";
		file << "add_executable(${PROJECT_NAME} ./src/main.cc)\n";
		file << "install(TARGETS ${PROJECT_NAME} DESTINATION bin)\n";
		file.close();
	};
};
