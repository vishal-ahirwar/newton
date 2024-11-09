#define RELEASE
#include "app.h"
//2.0
extern int argCount{};
void test() {

};

int main(int argc, char *argv[])
{
#ifndef RELEASE
    test();
#else
    if (argc < 2)
        return CLI::showHelp();
    argCount = argc;
    return CLI::createApp((const char **) argv, argc);
#endif
};
