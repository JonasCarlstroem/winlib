#pragma once

#include <tinyxml2.h>
#include <unordered_set>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "string_output.h"
#include "../include/comp/ui_manager.h"
#include "../include/comp/ui_element.h"

#define INCLUDE(name) "#include "#name

using namespace tinyxml2;
using namespace std;
using namespace comp;
namespace fs = filesystem;

typedef unordered_set<string> include_list;
typedef vector<string> statement_list;

const string OUTPUT_FILE = "src/ui_components.cpp";
const string OUTPUT_DIR = "bindings";

string get_base_name(const string& path) {
    return fs::path(path).stem().string();
}

string get_tag_name(const string& name) {
    string tag(name);
    for (auto& c = tag.begin(); c != tag.end(); ++c) {
        if (*c == '_') {
            *c = '-';
        }
    }

    return tag;
}

string get_tag(XMLElement* xml) {
    return xml->Name();
}

string get_id(XMLElement* xml) {
    const XMLAttribute* attrib = xml->FindAttribute("id");
    if (attrib == nullptr) {
        throw exception("Error: missing required attribute 'id'");
    }

    return attrib->Value();
}

string get_width(XMLElement* xml) {
    const XMLAttribute* attr = xml->FindAttribute("width");
    if (attr == nullptr)
        return "";

    return attr->Value();
}

string get_height(XMLElement* xml) {
    const XMLAttribute* attr = xml->FindAttribute("height");
    if (attr == nullptr)
        return "";

    return attr->Value();
}

void extract_attributes(ui_element* el, XMLElement* xml) {
    el->set_attribute("type", get_tag(xml));
    el->set_attribute("id", get_id(xml));
    el->set_attribute("width", get_width(xml));
    el->set_attribute("height", get_height(xml));
}

ui_element* parse_element(XMLElement* xml) {
    if (!xml) return nullptr;
    
    ui_element* el = new ui_element();
    extract_attributes(el, xml);
    /*el->type() = xml->Name();
    el->id() = xml->Attribute("id") ? xml->Attribute("id") : "";*/

    for (const XMLAttribute* attr = xml->FirstAttribute(); attr; attr = attr->Next()) {
        el->set_attribute(attr->Name(), attr->Value());
    }

    XMLElement* xml_child = xml->FirstChildElement();
    while (xml_child) {
        if (false) {

        }
        else {
            el->add_child(parse_element(xml_child));
        }

        xml_child = xml_child->NextSiblingElement();
    }

    return el;
}

string generate_header_content(string class_name, ui_element* el) {
    if (!el) return "";

    ostringstream str;
    const char* t = "t";
    str << _pragma("once") << _newline;
    str << _include("ui_element.h") << _newline<2>;
    str << _class(class_name) << _inherit("public", "ui_element") << _open_bracket << _newline;
    str << "public:" << _newline;

    for (const auto& child : el->get_children()) {
        str << _tab << child->type() << "* " << child->id() << ";" << _newline;
    }

    for (const auto& child : el->get_children()) {
        for (const auto& attr : child->get_attributes()) {
            if (attr.first.find("on") == 0) {
                str << _tab << _func_def(_virtual("void"), attr.second) << _newline;
                /*str << _tab << _virtual("void") << _space << attr.second << _openclose_parenthesis<false> << _space << _openclose_brackets << _newline;*/
            }
        }
    }

    str << _tab << _call(class_name, true) << _newline;
    str << _closing_bracket << _newline;

    return str.str();
}

string generate_source_content(string class_name, ui_element* el) {
    if (!el) return "";

    ostringstream str;
    str << _include(class_name + ".h") << _newline<2>;
    str << class_name << "::" << class_name << _openclose_parenthesis<false> << _open_bracket << _newline;

    for (const auto& child : el->get_children()) {
        str << _tab << _var("", child->id(), _new(child->type(), child->id()));
        str << _tab << _call("add_child", child->id()) << _newline;
    }

    str << _closing_bracket<false> << _newline;

    return str.str();
}

void generate_base_class(string class_name, ui_element* root, ofstream& output_header, ofstream& output_source) {
    if (!root) return;

    //string class_name = "_" + root->type();
    string h_content = generate_header_content(class_name, root);
    string cpp_content = generate_source_content(class_name, root);
    //ostringstream oos;

    output_header << h_content;
    output_source << cpp_content;

    output_header.close();
    output_source.close();
    //oos << _pragma("once") << _newline;
    //oos << _include("ui_element.h") << _newline<2>;
    //oos << _class(class_name) << _inherit("public", "ui_element") << _open_bracket << _newline;
    //oos << "public:" << _newline;

    //for (const auto& child : root->get_children()) {
    //    oos << _tab << child->type() << "* " << child->id() << ";" << _newline;
    //}

    //for (const auto& child : root->get_children()) {
    //    for (const auto& attr : child->get_attributes()) {
    //        if (attr.first.find("on") == 0) {
    //            oos << _tab << _virtual("void") << _space << attr.second << _openclose_parenthesis << _openclose_brackets << _newline;
    //        }
    //    }
    //}

    //oos << _tab << class_name << _openclose_parenthesis << _newline;
    //oos << _closing_bracket << _newline;

    //string header = oos.str();
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
        string tag_name = get_tag_name(base_name);

        ui_element* root_el = parse_element(doc.FirstChildElement(tag_name.c_str()));
        fs::path out_h_f = fs::path("bindings") / fs::path("_" + base_name + ".h");
        fs::path out_cpp_f = fs::path("bindings") / fs::path("_" + base_name + ".cpp");

        ofstream out_h(out_h_f);
        ofstream out_cpp(out_cpp_f);
        generate_base_class(string("_" + base_name), root_el, out_h, out_cpp);

        //XMLElement* root = doc.FirstChildElement("template");
        //if (!root) {
        //    cerr << "Error: No <template> root element in " << xmlFile << "\n";
        //    return;
        //}

        //string bind_function = "void bind_" + base_name + "_ui(ui_manager& manager) {\n";

        //for (XMLElement* el = root->FirstChildElement(); el;  el = el->NextSiblingElement()) {
        //    string tag = el->Name();
        //    string cpp_class = tag;
        //    string comp_id = el->Attribute("id") ? el->Attribute("id") : "";

        //    if (!comp_id.empty()) {
        //        includes.insert("#include \"" + base_name + ".h\"");
        //        member_vars.push_back("\tstd::shared_ptr<" + base_name + "> " + comp_id + ";");
        //        registrations.push_back("\t" + comp_id + " = std::make_shared<" + base_name + ">(\"" + comp_id + "\");");
        //        registrations.push_back("\tmanager.register_element(" + comp_id + ");");
        //    }

        //    bind_function += "\tauto " + comp_id + " = std::make_shared<" + cpp_class + ">(\"" + comp_id + "\");\n";
        //    bind_function += "  manager.register_element(" + comp_id + ");\n";
        //}

        //bind_function += "}\n";

        //binding_functions.push_back(bind_function);
        //all_bind_calls.push_back("  bind_" + base_name + "_ui(manager);");
    }

    //write_source_file(includes, binding_functions, all_bind_calls);

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
            string cpp_file = string(entry.path().stem().string() + ".cpp");
            string xml_file = entry.path().string();
            mapping_file << xml_file << ":src/" << cpp_file << _newline;
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