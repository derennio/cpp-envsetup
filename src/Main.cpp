#define __E_VERSION__ "0.1"

#include <iostream>
#include <json/json.h>
#include <getopt.h>

#include "file/FileUtils.hpp"
#include "json/EnvConfigJson.hpp"
#include "json/JsonParser.hpp"
#include "batch/BatchConverter.hpp"

const char * const HELPTXT = {
    "Usage: EnvSetup [OPTIONS] file [file2] ...\n" \
    "-h, --help             Display this information\n" \
    "    --debug            Enable debug mode\n" \
    "-v, --version          Display current version number\n" \
    "\n" \
    "EnvSetup is a tool written by Maria Birrenbach, Arne Sponer, Niklas Roth and Ennio Haibach\n" \
    "For more information contact haibach.ennio-it23@it.dhbw-ravensburg.de, sponer.arne-it23@it.dhbw-ravensburg.de, roth.niklas-it23@it.dhbw-ravensburg.de or birrenbach.maria-it23@it.dhbw-ravensburg.de"
};

static int debug = {0};

const struct option longopts[] =
{
    { "debug", no_argument, &debug, 1 },
    { "help", no_argument, NULL, 'h' },
    { "version", no_argument, NULL, 'v' },
    { 0, 0, 0, 0 }
};

static void printHelp()
{
    puts(HELPTXT);
    exit(0);
}

static void printVersion()
{
    puts("Current version number " __E_VERSION__);
}

void processFiles(const std::vector<std::string> files)
{
    for(auto file : files) {
        if (debug) {
            std::cout << "Now parsing file: " << file << std::endl;
        }

        Json::Value jsonObject = FileUtils::parseJsonFile(file);
        EnvConfig envConfig = JsonParser::parseJson(jsonObject);

        std::cout << "Output file: " << envConfig.outputFile << std::endl;
        std::cout << "Hide shell: " << envConfig.hideShell << std::endl;
        for(auto entry : envConfig.entries) {
            std::cout << "Entry type: " << entry.type << std::endl;
            std::cout << "Entry key: " << entry.key << std::endl;
            std::cout << "Entry value: " << entry.value << std::endl;
        }
        std::cout << "Application: " << envConfig.application << std::endl;

        BatchConverter::convertToBatchScript(envConfig);
    }
}

void processArguments(int argc, char **argv)
{
    int optindex = {0};
    int c = {0};

    if (argc < 2) {
        printHelp();
        return;
    }

    while((c = getopt_long(argc, argv, "ho:v", longopts, &optindex)) >= 0)
    {
        switch(c)
        {
            case 0:
                printHelp();
                break;
            case 'h':
                printHelp();
                break;
            case 'v':
                printVersion();
                break;
            default:
                printHelp();
                break;
        }
    }

    std::vector<std::string> remainingArgs;
    for(int index = optind; index < argc; index++) {
        remainingArgs.push_back(argv[index]);
    }

    if (remainingArgs.size() > 0) {
        processFiles(remainingArgs);
    }
}

int main(int argc, char **argv) {
    processArguments(argc, argv);

    return 0;
}