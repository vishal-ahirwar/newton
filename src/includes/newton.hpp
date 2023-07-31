#ifndef __NEWTON__
#define __NEWTON__
#include "../includes/version.hpp"
#include <fstream>
#include <string.h>
#include <time.h>
#include <iostream>
namespace newton
{
    void createNewProject(char *argv[]);
    void compile();
    void run();
    void generateNewtonFile(const std::string&);
    void readNewtonFile(std::string&);
}
#endif