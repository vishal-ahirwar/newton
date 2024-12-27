#include "aura.hpp"
#include "colors.hpp"
#include <thread>
#include "constant.hpp"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif
#ifndef WIN32
#include <unistd.h>
#endif
#include <downloader.h>

#ifdef WIN32
#define USERNAME "USERPROFILE"
#else
#define USERNAME "USER"
#endif

#include <vector>
#include <algorithm>

void App::setupUnitTestingFramework()
{
	namespace fs = std::filesystem;
	auto path = fs::current_path().string() + "/tests/";
	if (fs::exists(path))
	{
		return;
	};
	fs::create_directory(path);

	std::fstream testFile(path + "main.cc", std::ios::out);
	if (testFile.is_open())
	{
		testFile << TEST_CXX_CODE;
		testFile.close();
	};

	std::ofstream file;
	file.open("CMakeLists.txt", std::ios::app);
	if (file.is_open())
	{
		file << TEST_CODE;
		file.close();
		printf("%s[Msg] : catch2 added for unit testing,start adding tests in tests/main.cc then run 'aura utest' to run tests:)%s\n", GREEN, WHITE);
	}
	else
	{
		printf("%s[error] : Failed to setup unit testing framework catch2 :(%s\n", RED, WHITE);
	}
}

void App::createNewProject(const char *argv[], int argc)
{
	clock_t start = clock(), end = 0;

	printf("%sCreating directory ....\n%s", GREEN, WHITE);

	std::string cmdString{};
	createDir(argv[2]);
	printf("%sGenerating Code for main.c and CMakeLists.txt ....\n%s", GREEN, WHITE);
	generateConanFile();
	generateCppTemplateFile(argv[2]);
	generateCmakeFile(argv[2]);
	generateauraFile(projectName);
	generateGitIgnoreFile();
	end = clock();

	printf("%sElapsed Time : %8.2fms\nWith great power comes great responsibility\n%s",
		   YELLOW,
		   difftime(end, start),
		   WHITE);
};

// TODO : add compile option
void App::compile(const std::string &additional_cmake_arg)
{
	// Temp Soln

	namespace fs = std::filesystem;
	std::string cpu_threads{std::to_string(std::thread::hardware_concurrency())};
	printf("%sThreads in use: %s%s\n", YELLOW, cpu_threads.c_str(), WHITE);
	if (!fs::exists(fs::current_path().string() + "/build") || additional_cmake_arg.length() > 5)
	{
		// run cmake
		printf("%sCompile Process has been started ....\n%s", BLUE, WHITE);
		reloadPackages();
		// run ninja
		if (!system(("ninja -C build/Release -j" + cpu_threads).c_str())) // if there is any kind of error then don't clear the terminal
			printf("\n%sBUILD SUCCESSFULL%s\n", GREEN, WHITE);
		else
			printf("\n%sBUILD FAILED%s\n", RED, WHITE);
	}
	else
	{
		// run ninja
		if (!system(("ninja -C build/Release -j" + cpu_threads).c_str())) // if there is any kind of error then don't clear the terminal
			printf("\n%sBUILD SUCCESSFULL%s\n", GREEN, WHITE);
		else
			printf("\n%sBUILD FAILED%s\n", RED, WHITE);
	}
};

void App::run(int argc,const char**argv)
{
	std::string output{};
	readauraFile(output);
	projectName = output;

	std::string run{};
	// printf("%s%s: \n%s", YELLOW, projectName.c_str(),WHITE);
#ifdef WIN32
	run += ".\\build\\Release\\";
	run += projectName;
	run += ".exe";
#else
	run += "./build/Release/";
	run += projectName;
#endif // WIN32
	for(int i=0;i<argc;++i)
	{
		run+=" ";
		run+=argv[i];
	};

	if (system(run.c_str()))
	{
		printf("%s\n[error] Maybe You should Compile First Before run or You have Permission to "
			   "execute program!\n%s",
			   RED,
			   WHITE);
	};
}

void App::build()
{
	this->compile();
	this->run(0,nullptr);
}

void App::addToPathWin()
{
#ifdef WIN32
	namespace fs = std::filesystem;
	std::string aura{getenv(USERNAME)};
	aura += "\\aura";
	std::string source{fs::current_path().string() + "\\aura.exe"};
	std::string destination{(aura + "\\aura.exe").c_str()};
	if (source.compare(destination) != 0)
	{
		if (!fs::exists(source))
		{
			std::cout << "aura doesn't exist in current dir\n";
		}
		else
		{
			printf("%sCopying aura into %s%s\n", GREEN, aura.c_str(), WHITE);
			fs::remove(destination);
			if (fs::copy_file(source, destination, fs::copy_options::overwrite_existing))
			{
				printf("%s copied to %s\n", source.c_str(), destination.c_str());
			}
			else
			{
				printf("%serror while copying aura.exe into aura directory!%s\n", RED, WHITE);
			};
		}
	}
	std::string path{aura + ";"};

	for (const auto &dir : fs::directory_iterator(aura))
	{
		if (dir.is_directory())
		{
			path += dir.path().string();
			if (path.find("conan") != std::string::npos)
			{
				path += ";";
				continue;
			}
			path += "\\bin;";
		}
	};

	std::string env{getenv("path")};
	// Split path by semicolons and check each path individually
	std::istringstream pathStream(path);
	std::string singlePath;
	bool found = true;
	std::string newPath{};
	while (std::getline(pathStream, singlePath, ';'))
	{
		if (env.find(singlePath) == std::string::npos)
		{
			found = false;
			newPath += singlePath;
			newPath += ";";
		}
	}

	if (found)
	{
		std::cout << "All paths from aura are in PATH\n";
	}
	else
	{
		std::cout << "Some paths from aura are missing in PATH adding these entries into path make sure to restart your shell after that\n";
		pathStream.clear();
		pathStream.str(newPath);
		std::string tempStr{};
		while (std::getline(pathStream, tempStr, ';'))
		{
			std::cout << tempStr << "\n";
		};
		system(("setx PATH \"%PATH%;" + newPath + "\"").c_str());
	}
#endif
}

void App::addToPathUnix()
{
	namespace fs = std::filesystem;
	std::string aura{"/home/"};
	aura += {getenv(USERNAME)};
	aura += "/aura";
	std::string source{fs::current_path().string() + "/aura"};
	std::string destination{(aura + "/aura").c_str()};
	if (source.compare(destination) != 0)
	{
		if (!fs::exists(source))
		{
			std::cout << "aura doesn't exist in current dir\n";
		}
		else
		{
			printf("%sCopying aura into %s%s\n", GREEN, destination.c_str(), WHITE);
			fs::remove(destination);
			if (fs::copy_file(source, destination, fs::copy_options::overwrite_existing))
			{
				printf("%s copied to %s\n", source.c_str(), destination.c_str());
			}
			else
			{
				printf("%serror while copying aura.exe into aura directory!%s\n", RED, WHITE);
			};
		}
	}
	std::string path{aura + ";"};
	for (const auto &dir : fs::directory_iterator(aura))
	{
		if (dir.is_directory())
		{
			if(path.find("_internal")!=std::string::npos)continue;
			path += dir.path().string();
			path+=";";
		};
	};
	std::string env{getenv("PATH")};
	// Split path by semicolons and check each path individually
	std::istringstream pathStream(path);
	std::string singlePath;
	bool found = true;
	std::string newPath{};
	while (std::getline(pathStream, singlePath, ';'))
	{
		std::cout<<singlePath<<"\n";
		if (env.find(singlePath) == std::string::npos)
		{
			found = false;
			newPath += singlePath;
			newPath += ";";
		}
	}

	if (found)
	{
		std::cout << "All paths from aura are in PATH\n";
	}
	else
	{
		std::cout << "Some paths from aura are missing in PATH adding these entries into path make sure to restart your shell after that\n";
		pathStream.clear();
		pathStream.str(newPath);
		std::string tempStr{};
		std::string bashrc = std::string("/home/") + getenv(USERNAME) + "/.bashrc";
		std::fstream file(bashrc.c_str(), std::ios::app);
		if (file.is_open())
		{
			file << "export PATH=$PATH:" << newPath << "\n";
			file.close();
		}
		else
		{
			std::cout << "failed to open ~/.bashrc file!\n";
			return;
		}
	};
};

void App::installEssentialTools(bool &isInstallationComplete)
{
#ifdef WIN32
	namespace fs = std::filesystem;
	printf("%sThis will install C/C++ GCC Toolchain with cmake and ninja from Github,\nAre you sure you "
		   "want to "
		   "continue??[y/n] %s\n",
		   YELLOW,
		   WHITE);
	std::string input{};
	std::cin >> input;
	if (tolower(input[0]) != 'y')
		return;
	std::string home = getenv(USERNAME);
	if (!home.c_str())
		return;
	home += "\\aura";
	printf("%sinstalling C/C++ GCC Toolchain with cmake ninja and conan package manager please wait....%s\n", BLUE, WHITE);
	// TODO
	printf("%sInstall winlibs Intel/AMD (0).32-bit and (1).64-bit standalone build 0/1?%s\n", BLUE, WHITE);
	std::cin >> input;
	if (input == "0")
	{
		Downloader::download(std::string(COMPILER_URL_32BIT), home + "\\compiler.zip");
		Downloader::download(std::string(CMAKE_URL_32BIT), home + "\\cmake.zip");
		Downloader::download(std::string(CONAN_URL_32BIT), home + "\\conan.zip");
	}
	else if (input == "1")
	{
		Downloader::download(std::string(COMPILER_URL_64BIT), home + "\\compiler.zip");
		Downloader::download(std::string(CMAKE_URL_64BIT), home + "\\cmake.zip");
		Downloader::download(std::string(CONAN_URL_64BIT), home + "\\conan.zip");
	}
	else
	{
		printf("Invalid install command, try again\n");
		return;
	}

	printf("%sunzipping file at %s%s\n", BLUE, home.c_str(), WHITE);
	if (system((std::string("tar -xf ") + "\"" + home + "\\compiler.zip\"" + " -C " + "\"" + home + "\"").c_str()))
		return;
	if (system((std::string("tar -xf ") + "\"" + home + "\\cmake.zip\"" + " -C " + "\"" + home + "\"").c_str()))
		return;
	if (system((std::string("tar -xf ") + "\"" + home + "\\conan.zip\"" + " -C " + "\"" + home + "\"").c_str()))
		return;
	printf("%sremoving downloaded archives...%s\n", RED, WHITE);
	fs::remove((home + "\\compiler.zip"));
	fs::remove((home + "\\cmake.zip"));
	fs::remove((home + "\\conan.zip"));

	isInstallationComplete = true;
	addToPathWin();
#else
#define DISTRO_INFO "/etc/os-release"
	// Todo :read the file and u will know what ditro user running ;)
	try
	{
		namespace fs = std::filesystem;
		std::string aura{"/home/"};
		aura += {getenv(USERNAME)};
		aura += "/aura";
		Downloader::download(std::string(CONAN_LINUX_URL),aura+"/conan.tgz");
		system(("tar -xvf "+aura+"/conan.tgz"+" -C "+aura).c_str());
		system(("chmod +x "+aura+"/bin/conan").c_str());
		addToPathUnix();
		std::ifstream file(DISTRO_INFO);
		if (!file.is_open())
			return;
		std::string distro_name{};
		while (std::getline(file, distro_name))
		{
			if (distro_name.find("ID_LIKE") != std::string::npos)
				break;
		};
		if (distro_name.find("ID_LIKE") == std::string::npos)
		{
			file.clear();
			file.seekg(0, file.beg);
			while (std::getline(file, distro_name))
			{
				if (distro_name.length() > 0 && distro_name.substr(0, 2) == "ID")
					break;
			};
		}
		auto index = distro_name.find("=");
		if (index == std::string::npos)
			return;
		distro_name = distro_name.substr(++index, distro_name.length());
		std::cout << GREEN << "Development OS Distro/Parent Distro : " << distro_name << WHITE << "\n";
		if (distro_name.find("debian") != std::string::npos || distro_name.find("ubuntu") != std::string::npos)
		{
			system("sudo apt install g++ cmake git");
		}
		else if (distro_name.find("arch") != std::string::npos)
		{
			system("pacman -Sy g++ cmake git");
		}
		else if (distro_name.find("fedora") != std::string::npos || distro_name.find("rhel") != std::string::npos)
		{
			system("sudo dnf install g++ cmake git");
		};

		file.close();

		isInstallationComplete = true;
	}
	catch (std::exception &e)
	{
		printf("%sError : %s\nmake sure you have root privileges  to run this command%s\n", RED, e.what(), WHITE);
	};

#endif
};

void App::setup()
{
	onSetup();
};

void App::generateauraFile(const std::string &path)
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

void App::readauraFile(std::string &output)
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
		printf("%saura file setting.nn doesn't exist!\n%s", RED, WHITE);
	};
}

void App::createDir(const char *argv)
{
	namespace fs = std::filesystem;
	std::string cmdString{};
	projectName = argv;
	cmdString += argv;
	if (fs::create_directory(cmdString.c_str()))
	{
		cmdString += "/src";
		fs::create_directory(cmdString.c_str());
		cmdString += "/includes";
		fs::create_directory(cmdString.c_str());
		auto pos = cmdString.find("/");
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
		file << "project(" << argv << ")\n";
		file << CMAKE_CODE << "\n";
		file << "set(SOURCE ./src/main.cc)#add your additional source file here!\n";
		/*
		set(SOURCE ./src/main.cc ./src/player.cc ./src/person.cc)
		add_executable(${PROJECT_NAME} ${SOURCE})*/
		file << "add_executable(${PROJECT_NAME} ${SOURCE})\n";
		file << "install(TARGETS ${PROJECT_NAME} DESTINATION bin)\n";
		file << "#@link\n";
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
		printf("%s[Error]Failed to Generate License.txt, You may need to create License.txt by "
			   "yourself :)%s",
			   RED,
			   WHITE);
		return;
	};
	out << LICENSE_TEXT;
	out.close();
}
void App::generateConanFile()
{
	std::ofstream file;
	file.open("./" + projectName + "/conanfile.txt", std::ios::out);
	if (file.is_open())
	{
		file << CONAN_CODE;
		file.close();
	}
	else
	{
		printf("%s[error]Failed to generate conanfile.txt%s\n", RED, WHITE);
	};
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
			printf("%s[Msg]CPack added to cmake run 'cpack' command from build directory to build "
				   "a installer :)%s\n",
				   GREEN,
				   WHITE);
	}
	else
	{
		printf("%s[Msg]Something went wrong :(%s\n", RED, WHITE);
	}
};

void App::test()
{
	setupUnitTestingFramework();
	compile();
#ifdef WIN32
	system(".\\build\\tests.exe");
#else
	system("./build/tests");
#endif
};

bool App::onSetup()
{
	bool isInstallationComplete{false};
	namespace fs = std::filesystem;
#ifdef WIN32
	std::string home = getenv(USERNAME);
#else
	std::string home{"/home/"};
	home += getenv(USERNAME);
#endif
	if (!home.c_str())
		return false;
	std::fstream file;
#ifdef WIN32
	if (!fs::create_directory(home + "\\aura"))
	{
		printf("%saura dir alread exist%s\n", GREEN, WHITE);
	};
	file.open((home + "\\aura\\.cconfig").c_str(), std::ios::in);
	if (file.is_open())
	{
		file >> isInstallationComplete;
		file.close();
		if (isInstallationComplete)
		{
			printf("%sCompiler is already installed if you think you messed up with aura installation please use this command aura fix %s\n", GREEN, WHITE);
			return true;
		}
	}
	else
	{
		file.open((home + "\\aura\\.cconfig").c_str(), std::ios::out);
		if (file.is_open())
		{
			installEssentialTools(isInstallationComplete);
			file << isInstallationComplete;
			file.close();
			return true;
		}
	}
	if (!isInstallationComplete)
	{
		installEssentialTools(isInstallationComplete);
		file.open((home + "\\aura\\.cconfig").c_str(), std::ios::out);
		if (file.is_open())
		{
			file << isInstallationComplete;
			file.close();
		}
	}
#else
	if (!fs::create_directory(home + "/aura"))
	{
		printf("%saura dir alread exist%s\n", GREEN, WHITE);
	}
	else
	{
		printf("%sCreating aura dir at %s %s\n", BLUE, home.c_str(), WHITE);
	};

	file.open((home + "/aura/.cconfig").c_str(), std::ios::in);
	if (file.is_open())
	{
		file >> isInstallationComplete;
		file.close();
		if (isInstallationComplete)
		{
			printf("%sCompiler is already installed if you think you messed up with aura installation please use this command aura fix %s\n", GREEN, WHITE);
			return true;
		}
	}
	else
	{
		std::cout << "config file doesn't exist, creating one\n";
	};

	installEssentialTools(isInstallationComplete);

	file.open((home + std::string("/aura/.cconfig")).c_str(), std::ios::out);
	if (file.is_open())
	{
		std::cout << "writing to config file!\n";
		file << isInstallationComplete;
		file.close();
		std::cout << "done!\n";
		return true;
	}
	else
	{
		std::cout << "failed to write config file\n";
		return false;
	};

#endif
}

void App::fixInstallation()
{
	printf("%sAre you sure you "
		   "want to "
		   "continue??[y/n] %s\n",
		   YELLOW,
		   WHITE);
	std::string input{};
	std::cin >> input;
	if (tolower(input[0]) != 'y')
		return;
#ifdef WIN32
	std::string home = getenv(USERNAME);
#else
	std::string home{"/home/"};
	home += getenv(USERNAME);
#endif
	namespace fs = std::filesystem;
	printf("%sreseting aura...%s\n", RED, WHITE);
#ifdef WIN32
	fs::remove_all((home + "\\aura"));
#else
	fs::remove_all((home + "/aura"));
#endif
	printf("%sall clean!%s\n", RED, WHITE);
	setup();
};

void createProcess(const std::string &path)
{
#ifdef WIN32
	STARTUPINFO si = {sizeof(si)};
	PROCESS_INFORMATION pi;
	if (CreateProcessA(
			path.c_str(),		// Path to updater executable
			NULL,				// Command line arguments
			NULL,				// Process handle not inheritable
			NULL,				// Thread handle not inheritable
			FALSE,				// No handle inheritance
			CREATE_NEW_CONSOLE, // Run without opening a console window
			NULL,				// Use parent's environment
			NULL,				// Use parent's starting directory
			&si,				// Pointer to STARTUPINFO
			&pi					// Pointer to PROCESS_INFORMATION
			))
	{
		// Close process and thread handles
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		printf("%sUpdater started successfully.%s\n", GREEN, WHITE);
	}
	else
	{
		printf("%sFailed to start updater!\n", RED, WHITE);
		if (GetLastError() == 740)
		{
			printf("%sPlease try run this command with administrator privileges%s\n", RED, WHITE);
		}
		else
		{
			printf("%sunkown error occured!%s\n", RED, WHITE);
		};
	}
#else
	printf("%sImpementation is still in development for linux%s\n", BLUE, WHITE);
	// Linux implementation using fork() and exec()
	pid_t pid = fork(); // Create a new process

	if (pid < 0)
	{
		std::cerr << "Fork failed!" << std::endl;
		return;
	}

	if (pid == 0)
	{
		// This is the child process
		// Execute the update tool
		if (execlp(path.c_str(), path.c_str(), (char *)NULL) == -1)
		{
			printf("Failed to start update tool\n");
			return;
		};
	}
	else
	{
		// Parent process - can optionally wait for the child to finish or log the success
		std::cout << "Updater started successfully in the background." << std::endl;
		return;
	}
#endif
}

void App::update()
{
	namespace fs = std::filesystem;
#ifdef WIN32
	std::string aura = getenv(USERNAME);
#else
	std::string aura{"/home/"};
	aura += getenv(USERNAME);
#endif
#ifdef WIN32
	aura += "\\aura";
	std::string source{aura + "\\utool.exe"};
#else
	aura += "/aura";
	std::string source{aura + "/utool"};
#endif
	printf("updating aura...\n");
	std::cout << source << "\n";
	if (fs::exists(source))
	{
		createProcess(source);
	}
	else
	{
		Downloader::download(std::string(UPDATER_URL), source);
#ifndef WIN32
		system(("chmod +x " + source).c_str());
#endif
		createProcess(source);
	};
}
void App::debug()
{
	readauraFile(projectName);
	compile("-DCMAKE_BUILD_TYPE=Debug");
	system(("gdb ./build/" + projectName).c_str());
};

void App::release()
{
	readauraFile(projectName);
	compile("-DCMAKE_BUILD_TYPE=Release");
}
void addToConanFile(const std::string &name)
{
	std::ifstream in("conanfile.txt");
	if (!in.is_open())
	{
		printf("%s[error]Failed to open conanfile.txt%s\n", RED, WHITE);
		return;
	};
	std::vector<std::string> lines{};
	std::string line{};
	while (std::getline(in, line))
	{
		lines.push_back(line);
	};
	in.close();
	lines.insert(lines.begin() + 1, name);
	std::ofstream out("conanfile.txt");
	if (!out.is_open())
		return;
	for (const auto &l : lines)
	{
		out << l << "\n";
	};
	out.close();
}

void addToCMakeFile(std::string name)
{
	auto index = name.find("/");
	name = name.substr(0, index);
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	std::ifstream in("CMakeLists.txt");
	if (!in.is_open())
	{
		printf("%s[error]Failed to open CMakeLists.txt%s\n", RED, WHITE);
		return;
	};
	std::vector<std::string> lines{};
	std::string line{};
	while (std::getline(in, line))
	{
		lines.push_back(line);
	};
	in.close();
	auto pos = lines.size() - 1;
	for (int i = 0; i < lines.size(); ++i)
	{
		if (lines[i].find("#@find") != std::string::npos)
		{
			pos = ++i;
			break;
		};
	};
	lines.insert(lines.begin() + pos, "find_package(" + name + " REQUIRED)");
	lines.push_back("target_link_libraries(${PROJECT_NAME} " + name + "::" + name + ")");
	std::ofstream out("CMakeLists.txt");
	if (!out.is_open())
		return;
	for (const auto &l : lines)
	{
		out << l << "\n";
	};
	out.close();
};

void App::add(const std::string &name)
{
	addToConanFile(name);
	if (system("conan install . --build=missing"))
		return;
	printf("%s[Msg] : %s added to conanfile.txt and installed successfully%s\n", GREEN, name.c_str(), WHITE);
	addToCMakeFile(name);
	reloadPackages();
};

void App::reloadPackages()
{
	if (system("conan install . --build=missing"))
		return;
	if (system("cmake --preset conan-release -G \"Ninja\""))
		return;
};
