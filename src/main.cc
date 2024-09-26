#define RELEASE
#include "app.h"
//2.0
extern int argCount{};
int main(int argc, char *argv[])
{
    if (argc < 2)return CLI::showHelp();
    argCount = argc;
    return CLI::createApp((const char **)argv,argc);
};
