#include <iostream>
#include "colors.hpp"
#include <downloader.h>
constexpr std::string_view UPDATE_URL{"https://github.com/vishal-ahirwar/ccli/releases/latest/download/ccli.exe"};
int main()
{
    std::string home{getenv("USERPROFILE")};
    home += "\\ccli";
    printf("updating ccli...\n");
    Downloader::download(std::string(UPDATE_URL), home + "\\ccli.exe");
    printf("%sdone!%s\n", GREEN, WHITE);
    system("ccli");
    printf("Press any key to quit!\n");
    getchar();

    return 0;
}