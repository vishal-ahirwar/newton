#pragma once

#include <string>

class App
{
private:
    std::string projectName{};

public:
      void createNewProject(const char *argv[],int);
      void compile(const std::string&additional_cmake_arg="");
      void run();
      void build();
      void setup();
      void createInstaller();
      void test();
      void fixInstallation();
      void update();
      void debug();
      void release();
      void add(const std::string&);
      void reloadPackages();
private:
      void generateauraFile(const std::string &);
      void readauraFile(std::string &);
      void createDir(const char *);
      void generateCppTemplateFile(const char *);
      void generateCmakeFile(const char *);
      void generateGitIgnoreFile();
      void setupUnitTestingFramework();
      void generateLicenceFile();
      void generateConanFile();
private:
    bool onSetup();
    void installEssentialTools(bool&);
    void addToPathUnix();
    void addToPathWin();
    friend void test();
   
};
