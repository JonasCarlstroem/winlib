#include <tinyxml2.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "include/comp/ui_manager.h"

using namespace tinyxml2;
using namespace std;
namespace fs = filesystem;

string get_base_name(const string& path) {
    return fs::path(path).stem().string();
}

void generate_cpp(const std::string& mappingFile) {
    ifstream map(mappingFile);
    if (!map.is_open()) {
        cerr << "Could not read mapping file" << endl;
    }
    
    string currentLine;
    while (getline(map, currentLine)) {
        istringstream tokenizer(currentLine);

        string xmlFile;
        string cppFile;

        getline(tokenizer, xmlFile, ':');
        getline(tokenizer, cppFile);

        XMLDocument doc;
        if (doc.LoadFile(xmlFile.c_str()) != XML_SUCCESS) {
            cerr << "Failed to load " << xmlFile << endl;
            return;
        }

        string baseName = get_base_name(xmlFile);
        //string cppFile = fs::path(baseName + ".cpp").string();

        ofstream outFile(cppFile);
        if (!outFile.is_open()) {
            cerr << "Error opening file " << cppFile << endl;
            return;
        }

        outFile << "#include \"ui_manager.h\"\n";
        outFile << "#include \"" << baseName << ".h\"\n\n";
        outFile << "void Bind" << baseName << "UI() {\n";

        XMLElement* root = doc.FirstChildElement("ui");
        if (!root) {
            cerr << "Error: No <window> root element in " << xmlFile << "\n";
            return;
        }

        for (XMLElement* el = root->FirstChildElement(); el;  el = el->NextSiblingElement()) {
            const char* id = el->Attribute("id");
            if (id) {
                outFile << "    auto " << id << " = manager.find_ui_element(\"" << id << "\");\n";
            }
        }

        outFile << "}\n";
        outFile.close();
        cout << "Generated " << cppFile << " successfully!\n";
    }
}

void generate_mapping_file(const string& xml_dir, const string& output_file) {
    ofstream mapping_file(output_file);

    for (const auto& entry : fs::directory_iterator(xml_dir)) {
        if (entry.path().extension() == ".xml") {
            string base_name = entry.path().stem().string();
            string p = entry.path().string();
            mapping_file << p << ":src/" << base_name << ".cpp\n";
        }
    }
}

void load_ui_from_xml(const string& xml_file) {
    XMLDocument doc;
}

class flag {
public:
    enum flags {
        cpp,
        mf,
    };

    flag(const char* fl, const char* file) : _file(file) {
        string sf;
        if (fl[0] == '-') {
            sf = &fl[1];
        }
        else {
            sf = fl;
        }
        
        if (sf == "cpp") {
            _fl = cpp;
        }
        else if (sf == "mf") {
            _fl = mf;
        }
        else {
            throw exception("Invalid flag");
        }
    }

private:
    flags _fl;
    const char* _file;
};

vector<flag> parse_flags(int argc, const char** argv) {
    vector<flag> flags;

    if (argc > 1) {
        const char* szFlag = argv[0];
        const char* fName = argv[1];

        flag fl(szFlag, fName);
        flags.push_back(fl);
    }

    return flags;
}

int main(int argc, const char** argv) {
    //tinyxml2::XMLDocument doc;
    //if (doc.LoadFile("test.xml") != XML_SUCCESS) {
    //    return -1;
    //}
    if (argc < 2) return -1;

    //auto flags = parse_flags(argc, argv);

    generate_mapping_file("include\\comp", "mappings.txt");
    generate_cpp("mappings.txt");
    return 0;
}