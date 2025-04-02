#include <tinyxml2.h>
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

