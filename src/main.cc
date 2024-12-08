#define RELEASE
#include <app.h>

extern int argCount{};

int main(int argc, char *argv[])
{
    if (argc < 2)return CLI::showHelp();
    argCount = argc;
    return CLI::createApp((const char **)argv, argc);
};
