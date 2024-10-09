#include "newton.hpp"
#include "colors.hpp"

#include <filesystem>
#include <ctime>
#include <string>
#include <stdio.h>
#include <fstream>
#include "constant.hpp"
#ifndef WIN32
#include <unistd.h>
#endif

void App::setupUnitTestingFramework()
{
	std::ofstream file;
	file.open("CMakeLists.txt", std::ios::app);
	if (file.is_open())
	{

		file << GTEST_CODE;
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

void addToPathWin32()
{
	printf("%sWould you like to add newton to PATH Variable?y/n%s", RED, WHITE);
	if (char c; scanf(" %c", &c), c != 'y' || c != 'Y')
		return;
	printf("%s[TODO]Adding newton to PATH variable%s\n", BLUE, WHITE);

	namespace fs = std::filesystem;
	auto current_path = fs::current_path().string();

	std::string path = "setx PATH \"%PATH%;" + current_path + "\"";
	if (!system(path.c_str()))
		printf("%s%s added to path %s\n", CYAN, current_path.c_str(), WHITE);
}
void addToPathUnix()
{
	printf("%sNot Availble on Linux :(%s\n", CYAN, WHITE);
};

void installDevelopmentStuffWin32()
{
	printf("%s[Important] Make sure run this command with administrator privileges%s\n", CYAN, WHITE);
	printf("%sThis will install MinGW-13 Compiler and CMake 3.30,\nAre you sure you want to continue??[y/n] %s\n", YELLOW, WHITE);
	if (char input; scanf(" %c", &input), input == 'y' || input == 'Y')
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
};

void App::setup()
{

#ifdef WIN32
	addToPathWin32();
	installDevelopmentStuffWin32();
#else
	addToPathUnix();
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

		auto pos = MAIN_CODE.find("@");
		std::string str{std::string("Hello, ") + projectName + std::string("\\nhappy coding journey :)\\n")};
		MAIN_CODE.insert(pos + 1, str);
		file << MAIN_CODE;
		file.close();
	};
}

void App::generateCmakeFile(const char *argv)
{
	std::ofstream file;
	file.open("./" + projectName + "/CMakeLists.txt", std::ios::out);
	if (file.is_open())
	{

		file << CMAKE_CODE << "\n";
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

		file << GITIGNORE_CODE;

		file.close();
	};
};

void App::generateLicenceFile()
{
	std::ofstream out;
	out.open("License.txt", std::ios_base::out);
	if (!out.is_open())
	{
		printf("%s[Error]Failed to Generate License.txt, You may need to create License.txt by yourself :)%s", RED, WHITE);
		return;
	};
	out << LICENSE_TEXT;
	out.close();
};

void App::createInstaller()
{
	std::ofstream file;
	file.open("CMakeLists.txt", std::ios::app);
	if (file.is_open())
	{
		file << CPACK_CODE;
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
