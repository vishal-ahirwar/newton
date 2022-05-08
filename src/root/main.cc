#define RELEASE
#include "../includes/version.hpp"
#include "../includes/newton.hpp"


int main(int argc, char *argv[])
{

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