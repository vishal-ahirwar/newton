#include"downloader.h"
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
void Downloader::download(const std::string &url, const std::string &outputFilePath)
{
    // Perform the HTTP GET request
    cpr::Response response = cpr::Get(cpr::Url{url});

    // Check if the download was successful
    if (response.status_code == 200)
    {
        // Open a file in binary mode to write the ZIP content
        std::ofstream outputFile(outputFilePath, std::ios::binary);

        // Write the response content to the file
        outputFile.write(response.text.c_str(), response.text.size());
        outputFile.close();

        std::cout << "file downloaded and saved as " << outputFilePath << "\n";
    }
    else
    {
        std::cerr << "Failed to download file. Status code: " << response.status_code << "\n";
    }
}
