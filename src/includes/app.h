#ifndef APP
#define APP
#include "../includes/version.hpp"
#include "../includes/newton.hpp"
#include <string>
namespace CLI
{
    int showHelp();
    int createApp(const char *argv[]);
}
#endif