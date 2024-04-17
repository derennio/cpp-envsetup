#ifndef BATCH_CONVERTER_HPP
#define BATCH_CONVERTER_HPP

#include <string>
#include "../json/EnvConfigJson.hpp"
#include "../file/FileUtils.hpp"

class BatchConverter {
public:
    static bool convertToBatchScript(const EnvConfig& config) {
        std::string content;

        content += "start cmd ";
        content += config.hideShell ? "/c" : "/k";
        content += "\n";

        // May as well disable output for when the console stays hidden.
        if (config.hideShell) {
            content += "@echo off\n\n";
        } 
        else 
        {
            content += "@echo off\n\n";
        }

        // Add environment variable assignments, path edits and executable calls
        for (const auto& variable : config.entries) {
            if (variable.type == EntryType::ENV) {
                content += "set " + variable.key + "=" + variable.value + "\n";
            } else if (variable.type == EntryType::EXE) {
                content += variable.value + "\n";
            } else if (variable.type == EntryType::PATH) {
                content += "set PATH=%PATH%;" + variable.value + "\n";
            }
        }

        if (!config.application.empty()) {
            content += "start \"" + config.application + "\"\n";
        }

        // Add file creation and content writing
        FileUtils::generateBatchFile(config.outputFile, content);

        return true;
    }
};

#endif // BATCH_CONVERTER_HPP