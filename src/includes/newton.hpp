#ifndef __NEWTON__
#define __NEWTON__
#include "../includes/version.hpp"
#include <fstream>
#include <string.h>
#include <time.h>
#include <iostream>
class App
{
private:
    std::string projectName;

public:
      void createNewProject(const char *argv[]);
      void compile();
      void run();
      void build();
      void setup();
private:
      void generateNewtonFile(const std::string &);
      void readNewtonFile(std::string &);
      void createDir(const char *);
      void generateCppTemplateFile(const char *);
      void generateCmakeFile(const char *);
      void generateGitIgnoreFile();
};

#endif