#define RELEASE
#include "../includes/version.hpp"
#include "../includes/newton.hpp"

int main(int argc, char *argv[])
{

    if (c_str_compare(argv[1], "create"))
    {
        initOnCreate(argv);
    }
    else if (c_str_compare(argv[1], "help"))
    {
        printf("[newton] Help Wizard ...\n");
    }
    else if (c_str_compare(argv[1], "compile"))
    {
        Compile();
    }
    else if (c_str_compare(argv[1], "run"))
    {
        run();
    }
    else
    {
        printf("[newton] Invalid Commands !\n");
        printf("shtting down :(\n");
    };

    return 0;
}