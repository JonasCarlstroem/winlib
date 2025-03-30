#include <tinyxml2.h>
#include <unordered_set>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "include/comp/ui_manager.h"

#define INCLUDE(name) "#include "#name

using namespace tinyxml2;
using namespace std;
namespace fs = filesystem;

typedef unordered_set<string> include_list;
typedef vector<string> statement_list;

const string OUTPUT_FILE = "src/ui_components.cpp";

string get_base_name(const string& path) {
    return fs::path(path).stem().string();
}

void write_source_file(include_list& includes, statement_list& binding_functions, statement_list& all_binding_calls) {
    ofstream out(OUTPUT_FILE);
    if (!out) {
        cerr << "Error writing file..." << endl;
        return;
    }

    out << INCLUDE("ui_manager") << endl;
    for (const auto& incl : includes) {
        out << incl << endl;
    }
    
    out << endl;

    for (const auto& func : binding_functions) {
        out << func << endl;
    }

    out << "void bind_all_ui(ui_manager& manager) {" << endl;
    for (const auto& call : all_binding_calls) {
        out << call << endl;
    }

    out << "}" << endl;

    cout << "Generated source file: " << OUTPUT_FILE << endl;
}

void generate_bindings(const std::string& mappingFile) {
    ifstream map(mappingFile);
    if (!map.is_open()) {
        cerr << "Could not read mapping file" << endl;
    }

    include_list includes;
    statement_list member_vars;
    statement_list registrations;
    statement_list binding_functions;
    statement_list all_bind_calls;
    
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

        string base_name = get_base_name(xmlFile);

        //if (base_name.find('_') > 0) {
        //    for (auto& c = base_name.begin(); c != base_name.end(); ++c) {
        //        if (*c == '_') {
        //            *c = '-';
        //        }
        //    }
        //}

        XMLElement* root = doc.FirstChildElement("template");
        if (!root) {
            cerr << "Error: No <window> root element in " << xmlFile << "\n";
            return;
        }

        //string file_stem = fs::path(xmlFile).stem().string();
        string bind_function = "void bind_" + base_name + "_ui(ui_manager& manager) {\n";

        for (XMLElement* el = root->FirstChildElement(); el;  el = el->NextSiblingElement()) {
            string tag = el->Name();
            string cpp_class = tag;
            string comp_id = el->Attribute("id") ? el->Attribute("id") : "";

            if (!comp_id.empty()) {
                includes.insert("#include \"" + base_name + ".h\"");
                member_vars.push_back("\tstd::shared_ptr<" + base_name + "> " + comp_id + ";");
                registrations.push_back("\t" + comp_id + " = std::make_shared<" + base_name + ">(\"" + comp_id + "\");");
                registrations.push_back("\tmanager.register_element(" + comp_id + ");");
            }

            bind_function += "\tauto " + comp_id + " = std::make_shared<" + cpp_class + ">(\"" + comp_id + "\");\n";

            //if (id) {
            //    outFile << "    auto " << id << " = manager.find_ui_element(\"" << id << "\");\n";
            //}
            bind_function += "  manager.register_element(" + comp_id + ");\n";
        }

        bind_function += "}\n";

        binding_functions.push_back(bind_function);
        all_bind_calls.push_back("  bind_" + base_name + "_ui(manager);");

        /*outFile << "}\n";
        outFile.close();*/
    }

    write_source_file(includes, binding_functions, all_bind_calls);

    //ofstream out(OUTPUT_FILE);
    //if (!out) {
    //    cerr << "Error creating file: " << OUTPUT_FILE << endl;
    //}

    //string t = INCLUDE("ui_manager.h");
    //out << "#include \"ui_manager.h\"\n";

    cout << "Generated successfully!\n";
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
    generate_bindings("mappings.txt");
    return 0;
}