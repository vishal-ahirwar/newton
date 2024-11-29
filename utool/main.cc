#include <iostream>
#include "colors.hpp"
#include <downloader.h>
#ifdef WIN32
constexpr std::string_view UPDATE_URL{"https://github.com/vishal-ahirwar/ccli/releases/latest/download/ccli.exe"};
#else
constexpr std::string_view UPDATE_URL{"https://github.com/vishal-ahirwar/ccli/releases/latest/download/ccli"};
#endif

#ifdef WIN32
#define USERNAME "USERPROFILE"
#else
#define USERNAME "USER"
#endif

int main()
{
#ifdef WIN32
    std::string home = getenv(USERNAME);
    home += "\\ccli";
#else
    std::string home{"/home/"};
    home += getenv(USERNAME);
    home+="/ccli";
#endif
    printf("updating ccli...\n");
#ifdef WIN32
    Downloader::download(std::string(UPDATE_URL), home + "\\ccli.exe");
#else
    Downloader::download(std::string(UPDATE_URL), home + "/ccli");
#endif
    printf("%sdone!%s\n", GREEN, WHITE);
    system("ccli");
    printf("Press any key to quit!\n");
    getchar();

    return 0;
}