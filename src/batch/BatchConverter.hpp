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

        content += "start cmd ";
        content += config.hideShell ? "/c" : "/k";
        content += "\r\n";

        // May as well disable output for when the console stays hidden.
        if (config.hideShell)
        {
            content += "@echo off\r\n\r\n";
        }
        else
        {
            content += "@echo off\n\n";
        }

        // Select environment variable set calls from json
        std::vector<Entry> envEntries;
        std::string setExtension = "set ";
        std::copy_if(config.entries.begin(), config.entries.end(), std::back_inserter(envEntries), [](const Entry &entry)
                     { return entry.type == EntryType::ENV; });

        // Build one combined set string
        for (int i = 0; i < envEntries.size(); i++)
        {
            if (i != envEntries.size() - 1)
            {
                setExtension += envEntries[i].key + "=" + envEntries[i].value + " && set ";
            }
            else
            {
                setExtension += envEntries[i].key + "=" + envEntries[i].value + "\r\n";
            }
        }

        content += setExtension;

        std::string pathExtension;

        // Add environment variable assignments, path edits and executable calls
        for (const auto &variable : config.entries)
        {
            if (variable.type == EntryType::EXE)
            {
                content += variable.value + "\r\n";
            }
            else if (variable.type == EntryType::PATH)
            {
                pathExtension += variable.value + ";";
            }
        }

        if (!pathExtension.empty())
        {
            content += "set PATH=%PATH%;" + pathExtension + "\r\n";
        }

        if (!config.application.empty())
        {
            content += "start \"" + config.application + "\"\r\n";
        }

        // Add file creation and content writing
        FileUtils::generateBatchFile(config.outputFile, content);

        return true;
    }
};

#endif // BATCH_CONVERTER_HPP