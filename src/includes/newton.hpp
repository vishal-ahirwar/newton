#pragma once

#include <string>

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