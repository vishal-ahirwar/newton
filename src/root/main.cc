#define RELEASE
#include "../includes/version.hpp"
#include "../includes/newton.hpp"


int main(int argc, char *argv[])
{
    if(argc<2)
    {
        printf("[Usage]: newton command project-name\n[command] create, compile, run, help!\n");
        return 0;
    };
    
    if (newton::c_str_compare(argv[1], "create"))
    {
        newton::initOnCreate(argv);
    }
    else if (newton::c_str_compare(argv[1], "help"))
    {
        printf("[newton] Help Wizard ...\n");
    }
    else if (newton::c_str_compare(argv[1], "compile"))
    {
        newton::Compile();
    }
    else if (newton::c_str_compare(argv[1], "run"))
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