#define RELEASE
#include"../includes/version.hpp"
#include"../includes/newton.hpp"


int main(int argc,char*argv[])
{
    
    if(c_str_compare(argv[1],"create"))
    {
        printf("[newton] Creating directory ....\n");
       
        char cmd[250]={NULL};
        add_to_command("mkdir ",argv[2],cmd);

        if(!system(cmd))
        printf("[newton] Directory Created Successfuly :)\n");
    };

    return 0;
}