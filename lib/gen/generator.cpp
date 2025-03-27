#include <Windows.h>
#include <tinyxml2.h>
#include <iostream>
#include <fstream>

using namespace tinyxml2;

void generate_cpp(const std::string& fileName, tinyxml2::XMLDocument& doc)
{

}

int main()
{
    const char* dir[MAX_PATH];
    if (GetCurrentDirectory(MAX_PATH, &dir))
    {

    }
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("test.xml") != XML_SUCCESS)
    {
        return -1;
    }

    generate_cpp("ui.cpp", doc);
    return 0;
}