#include <iostream>
#include <json/json.h>
#include <getopt.h>

const char * const HELPTXT = {
    "Usage: options [OPTIONS] file ...\n" \
    "-h, --help             Display this information\n" \
    "    --debug            Enable debug mode\n" \
    "-o <file>              Named output of these programm\n" \
    "-v, --version          Display Programm Information\n" \
    "\n" \
    "For more information contact team@us.de"
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
    puts("Version vom " __DATE__);
    exit(0);
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

    if (optind < argc) {
        printf("Nonoption arguments ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }
}

int main(int argc, char **argv) {
    Json::Value root;
    Json::Reader reader;
    std::string json = "{\"array\":[\"item1\",\"item2\"],\"not an array\":\"asdf\"}";
    bool parsingSuccessful = reader.parse(json, root);
    if (!parsingSuccessful) {
        std::cout << "Failed to parse JSON" << std::endl;
        return 1;
    }

    std::cout << root << std::endl;

    processArguments(argc, argv);

    return 0;
}