#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <string>
#include <fstream>
#include <json/json.h>
#include <filesystem>

class FileParser {
public:
    static Json::Value parseJsonFile(const std::string& filename) {
        std::ifstream file(filename);
        
        if (!std::filesystem::exists(filename)) {
            throw std::runtime_error("File does not exist: " + filename);
        }

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        Json::Value jsonObject;
        Json::CharReaderBuilder reader;
        std::string errs;
        if (!Json::parseFromStream(reader, file, &jsonObject, &errs)) {
            throw std::runtime_error("Failed to parse JSON file: " + errs);
        }

        file.close();

        return jsonObject;
    }
};

#endif // FILEPARSER_HPP