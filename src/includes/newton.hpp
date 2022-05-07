#ifndef __NEWTON__
#define __NEWTON__
#include "../includes/version.hpp"
#include<fstream>
#include<string.h>
#include<time.h>

void add_to_command(const char*,const char*,char*);
bool c_str_compare(const char*,const char*);
void initOnCreate(char*argv[]);
void Compile();
void run();
#endif