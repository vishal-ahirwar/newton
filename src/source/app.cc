#include "../includes/app.h"
namespace CLI
{
    int showHelp()
    {
        printf("[Usage]: newton command project-name\n[command] create, compile, run, help!\n");
        return 0;
    }
    int createApp(const char *argv[])
    {
        App app;
        if (std::string(argv[1]) == std::string("create"))
        {
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
        else
        {
            printf("[newton] Invalid Commands !\n");
            printf("shtting down :(\n");
            return 0;
        };
        return 0;
    };

}
