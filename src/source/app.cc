#include "app.h"
#include "colors.hpp"
#include "ccli.hpp"
#include "ccliConfig.h"

#include <string>
#include <stdio.h>

extern int argCount;
namespace CLI
{
    int showHelp()
    {
        printf(
            "%sAbout:\nLearning C/C++ and tired of creating files and folder and running .cpp,\ncompilling manually again n again\ntry this it does a lot for you \nlike creating full structured project\n"
            "which will have CMake file, good clean folder structure,.gitignore file, and commands to \nfacilitate your most of time learning C++ without creating \n"
            "a new project every time you want to learn a new concept in C/C++ ;)"
            "%s\n\nversion : %d.%d.%d\nAuthor: %s\n%s\n"
            "%s\n[Usage]: \n"
            "ccli [command] projectname\n"
            "\n[available commands]%s\n\n"
            "create- create a new C/C++ project [ccli create projectName]\n"
            "compile- compile the project[cd into project directory [ccli compile]]\n"
            "run- run the compiled binary make sure to compile the project before running this command\n"
            "help-show the help wizard\n"
            "build - compile and run the project with this single command\n"
            "setup - this command will install a g++ compiler and cmake to your system if not already installed\n"
            "gtest : to enable unit testing{ccli create test --gtest}\n"
            "createinstaller : to create packged build of your application\n"
            "fix : to fix the ccli installation\n%s",
            BLUE, YELLOW, ccli_VERSION_MAJOR, ccli_VERSION_MINOR, ccli_VERSION_PATCH,
            ccli_COMPANY, ccli_COPYRIGHT, CYAN, GREEN, WHITE);
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
        else if (std::string(argv[1]) == std::string("fix"))
        {
            app.fixInstallation();
        }
        else
        {
            printf("%s[Error] Invalid Command !%s\n", RED, WHITE);
            printf("Try again with 'ccli help' :(\n");
            return 0;
        };
        return 0;
    };

}
