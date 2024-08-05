#include "app.h"
#include "colors.hpp"
#include "newton.hpp"
#include "newtonConfig.h"

#include <string>
#include <stdio.h>

extern int argCount;
namespace CLI
{
    int showHelp()
    {
        printf(
            "%sAbout:\n Learning C/C++ and tired of creating files and folder and running .cpp,\n compilling manually again n again\n try this it does a lot for you \n like creating full structured project\n "
            "which will have CMake file, good clean folder structure,.gitignore file, and commands to \n facilitate your most of time learning C++ without creating \n "
            "a new project every time you want to learn a new concept in C/C++ ;)"
            "%s\n  \n \n version : %d.%d.%d\n Author: %s\n %s\n"
            "%s[Usage]: \n "
            "newton [command] projectname\n"
            "[available commands]%s\n "
            "create- create a new C/C++ project [newton create projectName]\n "
            "compile- compile the project[cd into project directory [newton compile]]\n "
            "run- run the compiled binary [make sure to compile the project before running this command[newton compile]]\n "
            "help-show the help wizard\n "
            "build - compile and run the project with this single command[cd into project dir containing cmakefile.txt [newton build]]\n "
            "setup - this command will install a g++ compiler and cmake to your system if not already installed\n "
            "gtest : to enable unit testing{newton create test --gtest}\n "
            "createinstaller : to create packged build of your application\n %s",
            BLUE, YELLOW, NEWTON_VERSION_MAJOR, NEWTON_VERSION_MINOR, NEWTON_VERSION_PATCH,
            NEWTON_COMPANY, NEWTON_COPYRIGHT, CYAN, GREEN, WHITE);
        return 0;
    }
    int createApp(const char *argv[], int argc)
    {
        App app;
        if (std::string(argv[1]) == std::string("create"))
        {
            if (argCount < 3)
            {
                printf("[Error]Project name can't be null!\n");
                return 1;
            };

            app.createNewProject(argv, argCount);
        }
        else if (std::string(argv[1]) == std::string("help"))
        {
            CLI::showHelp();
        }
        else if (std::string(argv[1]) == std::string("compile"))
        {
            app.compile();
        }
        else if (std::string(argv[1]) == std::string("run"))
        {
            app.run();
        }
        else if (std::string(argv[1]) == std::string("build"))
        {
            app.build();
        }
        else if (std::string(argv[1]) == std::string("setup"))
        {
            app.setup();
        }
        else if (std::string(argv[1]) == std::string("createinstaller"))
        {
            app.createInstaller();
        }
        else if (std::string(argv[1]) == std::string("gtest"))
        {
            app.gTest();
        }
        else
        {
            printf("%s[Error] Invalid Command !%s\n",RED,WHITE);
            printf("Try again with 'newton help' :(\n");
            return 0;
        };
        return 0;
    };

}
