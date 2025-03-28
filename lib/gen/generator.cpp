#include <Windows.h>
#include <tinyxml2.h>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace tinyxml2;

void generate_cpp(const std::string& fileName, tinyxml2::XMLDocument& doc)
{

}

int main()
{
    char buf = { 0 };
    if (!GetCurrentDirectory(MAX_PATH, &buf))
    {
        return -1;
    }
    std::string str(&buf);

    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("test.xml") != XML_SUCCESS)
    {
        return -1;
    }

    generate_cpp("ui.cpp", doc);
    return 0;
}