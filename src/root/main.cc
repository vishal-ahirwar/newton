#define RELEASE
#include "../includes/version.hpp"
#include "../includes/newton.hpp"
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("[Usage]: newton command project-name\n[command] create, compile, run, help!\n");
        return 0;
    };

    if (std::string(argv[1]) == std::string("create"))
    {
        newton::createNewProject(argv);
    }
    else if (std::string(argv[1]) == std::string("help"))
    {
        printf("[newton] Help Wizard ...\n");
    }
    else if (std::string(argv[1]) == std::string("compile"))
    {
        newton::compile();
    }
    else if (std::string(argv[1]) == std::string("run"))
    {
        newton::run();
    }
    else
    {
        printf("[newton] Invalid Commands !\n");
        printf("shtting down :(\n");
    };

    return 0;
}