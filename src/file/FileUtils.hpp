#ifndef FILEUTILS_HPP
#define FILEUTILS_HPP

#include <string>
#include <fstream>
#include <json/json.h>
#include <filesystem>

class FileUtils
{
public:
    static Json::Value parseJsonFile(const std::string &filename)
    {
        std::ifstream file(filename);

        if (!std::filesystem::exists(filename))
        {
            throw std::runtime_error("File does not exist: " + filename);
        }

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        Json::Value jsonObject;
        Json::CharReaderBuilder reader;
        std::string errs;
        if (!Json::parseFromStream(reader, file, &jsonObject, &errs))
        {
            throw std::runtime_error("Failed to parse JSON file: " + errs);
        }

        file.close();

        return jsonObject;
    }

    static void generateBatchFile(const std::string &fileName, const std::string &content)
    {
        std::ofstream file(fileName);

        if (!file.is_open())
        {
            throw std::runtime_error("Failed to create file: " + fileName);
        }

        file << ":: Automatically generated batch file. DO NOT EDIT!\r\n";
        file << content;

        file.close();
    }
};

#endif // FILEUTILS_HPP