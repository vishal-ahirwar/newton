#include "../includes/app.h"
#include"../includes/version.hpp"
extern int argCount;
namespace CLI
{
    int showHelp()
    {
        printf("version : %.2f\nAuthor: %s\n%s\n[Usage]: \nnewton command project-name\n[command] create, compile, run, help!\n",VERSION,COMPANY,COPYRIGHT);
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
