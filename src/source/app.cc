#include "../includes/app.h"
#include"../includes/version.hpp"
extern int argCount;
namespace CLI
{
    int showHelp()
    {
        printf("About: \n\tlearning C/C++ and tired of creating files and folder and running .cpp,\n\tcompilling manually again n again\n\ttry this it does a lot for you \n\tlike creating full structured project\n\t which will have cmakefile, good clean folder structure ,.gitignore file, and some commands to \n\tinvest your most of time in learning C++ not creating \n\t new project evry time you wanna to learn a new concept of c/c++ ;)\n\t \n \n\tversion : %.2f\n\tAuthor: %s\n\t%s\n[Usage]: \n\tnewton [command] projectname\n[available commands]\n\tcreate- create a new C/C++ project [newton create projectName]\n\tcompile- compile the project[cd into project directory [newton compile]]\n\trun- run the compiled binary [make sure to compile the project before running this command[newton compile]]\n\thelp-show the help wizard\n\tbuild - compile and run the project with this single command[cd into project dir containing cmakefile.txt [newton build]]\n",VERSION,COMPANY,COPYRIGHT);
        return 0;
    }
    int createApp(const char *argv[])
    {
        App app;
        if (std::string(argv[1]) == std::string("create"))
        {
            if (argCount < 3)
            {
                printf("[Error]Project name can't be null!\n");
                return 1;
            };

            app.createNewProject(argv);
        }
        else if (std::string(argv[1]) == std::string("help"))
        {
            printf("[newton] Help Wizard ...\n");
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
        else
        {
            printf("[newton] Invalid Commands !\n");
            printf("shtting down :(\n");
            return 0;
        };
        return 0;
    };

}
