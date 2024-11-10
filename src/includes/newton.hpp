#pragma once

#include <string>

class App
{
private:
    std::string projectName;

public:
      void createNewProject(const char *argv[],int);
      void compile();
      void run();
      void build();
      void setup();
      void createInstaller();
      void gTest();
      void fixInstallation();
private:
      void generateNewtonFile(const std::string &);
      void readNewtonFile(std::string &);
      void createDir(const char *);
      void generateCppTemplateFile(const char *);
      void generateCmakeFile(const char *);
      void generateGitIgnoreFile();
      void setupUnitTestingFramework();
      void generateLicenceFile();
private:
    bool onSetup();
    void installCompilerAndCMake(bool&);
    void addToPathUnix();
    void addToPathWin();
};