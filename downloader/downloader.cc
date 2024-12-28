#include"downloader.h"
#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
//progress bar
void Downloader::download(const std::string &url, const std::string &outputFilePath)
{
    std::string name = outputFilePath.substr(outputFilePath.find_last_of("/") + 1);
    // Perform the HTTP GET request
    cpr::Response response = cpr::Get(cpr::Url{url},cpr::ProgressCallback([&](cpr::cpr_off_t download_total,cpr::cpr_off_t download_now,cpr::cpr_off_t upload_total,cpr::cpr_off_t upload_now,intptr_t user_data)->bool{
        fprintf(stdout,"\rDownloading %s : %.2f%\n",name.c_str(),(download_now/download_total)*100.0);
    }));

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
