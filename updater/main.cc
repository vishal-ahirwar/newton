#include <iostream>
#include "colors.hpp"
constexpr std::string_view UPDATE_URL{"https://github.com/vishal-ahirwar/ccli/releases/latest/download/ccli.exe"};
int main()
{
    std::string home{getenv("USERPROFILE")};
    home += "\\ccli";
    printf("%supdating ccli...%s\n", BLUE, WHITE);

    if (!system((std::string("powershell -Command wget ") + std::string(UPDATE_URL) + std::string(" -o ") + home + "\\ccli.exe").c_str()))
    {
        printf("%sdone!%s\n", GREEN, WHITE);
        system("ccli");
    }
    else
    {
        printf("%sfailed to update!%s\n", RED, WHITE);
    };

    return 0;
}