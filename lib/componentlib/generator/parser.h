#include <tinyxml2.h>
#include <iostream>
#include <filesystem>
#include <string>
#include "../include/comp/ui_element.h"

using namespace tinyxml2;
using namespace std;
using namespace comp;
namespace fs = filesystem;

string format_tag(const string& name) {
    string tag(name);
    for (auto& c = tag.begin(); c != tag.end(); ++c) {
        if(*c == '_') {
            *c = '-';
        }
    }

    return tag;
}

void parse_xml(const fs::path& file) {
    XMLDocument doc;
    if (doc.LoadFile(file.string().c_str()) != XML_SUCCESS) {
        string msg = "Failed to load file " + file.string();
        throw exception(msg.c_str());
    }

    string class_name = file.stem().string();
    string tag = format_tag(class_name);

    XMLElement* rootXml = doc.FirstChildElement();
}