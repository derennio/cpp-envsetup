// EnvConfigJson.hpp
#ifndef DATASTRUCTS_HPP
#define DATASTRUCTS_HPP

#include <string>
#include <vector>

enum EntryType {
    ENV,
    EXE,
    PATH
};

struct Entry {
    EntryType type;
    std::string key;
    std::string value;
};

struct EnvConfig {
    std::string outputFile;
    bool hideShell;
    std::vector<Entry> entries;
    std::string application;
};

#endif // ENVCONFIGJSON_HPP