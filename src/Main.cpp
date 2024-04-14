#include <iostream>
#include <json/json.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Use jsoncpp
    Json::Value root;
    root["key"] = "value";
    std::cout << root << std::endl;

    return 0;
}