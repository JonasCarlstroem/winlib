#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include "utils.h"
using namespace std;

struct attribute;
struct attribute_group;

enum class xsd_builin_type {
    string,
    integer,
    boolean,
    float_,
    double_,
    datetime,
    base64Binary,
    custom
};

struct xsd_qname {
    xml_string namespace_uri;
    xml_string local_name;
};

struct xsd_type_ref {
    xml_string name;
    xsd_builin_type builtin = xsd_builin_type::custom;
};

struct xsd_attribute {
    xml_string name;
    xsd_type_ref type;

    bool is_required = false;
    xml_string default_value;
    optional<xsd_simple_type> inline_simple_type;
};

struct xsd_element {
    xml_string name;
    xsd_type_ref type;

    bool is_optional = false;
    bool is_array = false;
    int min_occurs = 1;
    int max_occurs = 1;

    unique_ptr<xsd_complex_type> anonymous_complex_type;
    optional<xsd_simple_type> inline_simple_type;
};

struct xsd_complex_type {
    xml_string name;
    vector<xsd_element> sequence;
    vector<xsd_attribute> attributes;

    xml_string base_type;
    bool is_abstract = false;
    bool mixed = true;
};

struct xsd_simple_type {
    xml_string name;
    xml_string base;

    vector<xml_string> enumerations;
    bool is_enumeration = false;
};

struct xsd_schema {
    xml_string target_namespace;
    vector<xsd_element> global_elements;
    vector<xsd_complex_type> complex_types;
    unordered_map<string, xsd_simple_type> global_simple_types;
    unordered_map<string, vector<xsd_attribute>> global_attribute_groups;
};

xsd_type_ref to_type_ref(const xml_string& type_str) {
    if (type_str == "xs:string") return { "xs:string", xsd_builin_type::string };
    if (type_str == "xs:int") return { "xs:int", xsd_builin_type::integer };
    if (type_str == "xs:boolean") return { "xs:boolean", xsd_builin_type::boolean };

    return { type_str, xsd_builin_type::custom };
}