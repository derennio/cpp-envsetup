#ifndef BATCH_CONVERTER_HPP
#define BATCH_CONVERTER_HPP

#include <string>
#include "../json/EnvConfigJson.hpp"
#include "../file/FileUtils.hpp"

class BatchConverter
{
public:
    static bool convertToBatchScript(const EnvConfig &config)
    {
        std::string content;

        // May as well disable output for when the console stays hidden.
        if (config.hideShell)
        {
            content += "@echo off\r\n\r\n";
        }
        else
        {
            content += "@echo on\r\n\r\n";
        }

        content += "C:\\Windows\\System32\\cmd.exe ";
        content += config.hideShell ? "/c \"" : "/k \"";

        // Select environment variable set calls from json
        std::vector<Entry> envEntries;
        std::string setExtension = "set ";
        std::copy_if(config.entries.begin(), config.entries.end(), std::back_inserter(envEntries), [](const Entry &entry)
                     { return entry.type == EntryType::ENV; });

        // Build one combined set string
        for (u_int32_t i = 0; i < envEntries.size(); i++)
        {
            if (i != envEntries.size() - 1)
            {
                setExtension += envEntries[i].key + "=" + envEntries[i].value + " && set ";
            }
            else
            {
                setExtension += envEntries[i].key + "=" + envEntries[i].value + ((envEntries.size() < config.entries.size()) ? " && " : "\r\n");
            }
        }

        content += setExtension;

        std::string pathExtension;

        // Add environment variable assignments, path edits and executable calls
        for (const auto &variable : config.entries)
        {
            if (variable.type == EntryType::EXE)
            {
                content += variable.value + " && ";
            }
            else if (variable.type == EntryType::PATH)
            {
                pathExtension += variable.value + ";";
            }
        }

        if (pathExtension.empty() && config.application.empty()) {
            content += ";";
        }

        if (!pathExtension.empty())
        {
            content += "set PATH=%PATH%;" + pathExtension + (!config.application.empty() ? " && " : "\"\r\n");
        }

        if (!config.application.empty())
        {
            content += "start " + config.application + "\"\r\n";
        }

        content += "@echo on\r\n";

        // Add file creation and content writing
        FileUtils::generateBatchFile(config.outputFile, content);

        return true;
    }
};

#endif // BATCH_CONVERTER_HPP