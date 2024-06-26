#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include "../file/FileUtils.hpp"
#include "EnvConfigJson.hpp"

class JsonParser {
public:
    static EnvConfig parseJson(const Json::Value& jsonValue) {
        // Parse the JSON content and convert it to EnvConfig
        EnvConfig envConfig;

        // Parse the output file
        if (jsonValue.isMember("outputfile")) {
            envConfig.outputFile = jsonValue["outputfile"].asString();
        } else {
            envConfig.outputFile = "output.bat";
        }

        // Parse the hideShell flag
        if (jsonValue.isMember("hideshell")) {
            envConfig.hideShell = jsonValue["hideshell"].asBool();
        } else {
            envConfig.hideShell = false;
        }

        // Parse the entries
        if (jsonValue.isMember("entries")) {
            const Json::Value& entries = jsonValue["entries"];
            for (const Json::Value& entry : entries) {
                Entry newEntry;

                // Parse the type
                if (entry.isMember("type")) {
                    std::string type = entry["type"].asString();
                    if (type == "ENV") {
                        newEntry.type = EntryType::ENV;

                        // Parse the key
                        if (entry.isMember("key")) {
                            newEntry.key = entry["key"].asString();
                        } else {
                            throw std::runtime_error("Entry key is missing");
                        }

                        // Parse the value
                        if (entry.isMember("value")) {
                            newEntry.value = entry["value"].asString();
                        } else {
                            throw std::runtime_error("Entry value is missing");
                        }
                    } else if (type == "EXE") {
                        newEntry.type = EntryType::EXE;

                        // Parse the command
                        if (entry.isMember("command")) {
                            newEntry.value = entry["command"].asString();
                        } else {
                            throw std::runtime_error("Entry command is missing");
                        }
                    } else if (type == "PATH") {
                        newEntry.type = EntryType::PATH;

                        // Parse the path
                        if (entry.isMember("path")) {
                            newEntry.value = entry["path"].asString();
                        } else {
                            throw std::runtime_error("Entry path is missing");
                        }
                    } else {
                        throw std::runtime_error("Invalid entry type: " + type);
                    }
                } else {
                    throw std::runtime_error("Entry type is missing");
                }

                // Add the new entry to the list
                envConfig.entries.push_back(newEntry);
            }
        }

        // Parse the application
        if (jsonValue.isMember("application")) {
            envConfig.application = jsonValue["application"].asString();
        } 

        // Check if the JSON contains other members
        for (const auto& member : jsonValue.getMemberNames()) {
            if (member != "application" && member != "entries" && member != "outputfile" && member != "hideshell") {
                throw std::runtime_error("Invalid member in JSON at position " + std::to_string(jsonValue.get(member, Json::Value()).getOffsetStart()) + ": " + member);
            }
        }

        // Return the parsed EnvConfig object
        return envConfig;
    }
};

#endif // JSON_PARSER_HPP