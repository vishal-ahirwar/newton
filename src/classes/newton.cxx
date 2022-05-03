#include"../includes/newton.hpp"

void add_to_command(const char*cmd,const char*user,char*CMD)
{
    int j=0;
    for(auto i=0;cmd[i]!='\0';++i)
    {
        CMD[i]=cmd[i];
        j=i;
    };
    CMD[++j]=' ';
    for(auto i=0;user[i]!='\0';++i,++j)
    {
        #ifndef RELEASE
        printf("%c",user[i]);
        #endif
        CMD[j]=user[i];
    };
    printf("\n");

};

bool c_str_compare(const char*str1,const char*str2)
{
    int i=0;
    while(str2[i]!='\0')
    {
        if(str1[i]!=str2[i])return false;
        ++i;
    };
    return true;
};
