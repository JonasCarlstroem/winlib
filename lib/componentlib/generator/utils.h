#pragma once
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>

using namespace xercesc;
using namespace std;

const XMLCh* XS_SCHEMA;
const XMLCh* XS_ATTRIBUTE_GROUP;
const XMLCh* XS_ATTRIBUTE;
const XMLCh* XS_ELEMENT;
const XMLCh* XS_COMPLEX_TYPE;

const XMLCh* ATTR_ELEMENT_FORM_DEFAULT;

void init_strings() {
    XS_SCHEMA = XMLString::transcode("xs:schema");
    XS_ATTRIBUTE_GROUP = XMLString::transcode("xs:attributeGroup");
    XS_ATTRIBUTE = XMLString::transcode("xs:attribute");
    XS_ELEMENT = XMLString::transcode("xs:element");
    XS_COMPLEX_TYPE = XMLString::transcode("xs:complexType");

    ATTR_ELEMENT_FORM_DEFAULT = XMLString::transcode("elementFormDefault");
}

struct tab {
private:
    int indent = 0;

public:
    void inc() {
        indent++;
    }

    void dec() {
        indent--;
    }

    int get() const {
        return indent;
    }

    operator int() {
        return indent;
    }
} _tab_;

template<class... T>
ostream& log(T... t) {
    cout << (_tab_ > 0 ? string(_tab_, '\t') : "");
    return ((cout << t), ...);
}

ostream& log_line() {
    return log("") << '\n';
}

template<class... T>
ostream& log_line(T... t) {
    return log(t...) << '\n';
}

string dom_node_type(DOMNode::NodeType nt) {
    switch (nt) {
        case DOMNode::NodeType::ELEMENT_NODE: return "ELEMENT_NODE";
        case DOMNode::NodeType::ATTRIBUTE_NODE: return "ATTRIBUTE_NODE";
        case DOMNode::NodeType::TEXT_NODE: return "TEXT_NODE";
        case DOMNode::NodeType::CDATA_SECTION_NODE: return "CDATA_SECTION_NODE";
        case DOMNode::NodeType::ENTITY_REFERENCE_NODE: return "ENTITY_REFERENCE_NODE";
        case DOMNode::NodeType::ENTITY_NODE: return "ENTITY_NODE";
        case DOMNode::NodeType::PROCESSING_INSTRUCTION_NODE: return "PROCESSING_INSTRUCTION_NODE";
        case DOMNode::NodeType::COMMENT_NODE: return "COMMENT_NODE";
        case DOMNode::NodeType::DOCUMENT_NODE: return "DOCUMENT_NODE";
        case DOMNode::NodeType::DOCUMENT_TYPE_NODE: return "DOCUMENT_TYPE_NODE";
        case DOMNode::NodeType::DOCUMENT_FRAGMENT_NODE: return "DOCUMENT_FRAGMENT_NODE";
        case DOMNode::NodeType::NOTATION_NODE: return "NOTATION_NODE";
        default: return "UNKNOWN";
    }
}

string& xml_to_string(const XMLCh* xmlch) {
    char* cstr = XMLString::transcode(xmlch);
    string str(cstr);
    XMLString::release(&cstr);
    return str;
}

class xml_string {
private:
    string          _value;
    const XMLCh*    _xml_value;

    xml_string(string value, const XMLCh* xml_value) : _value(value), _xml_value(xml_value) {
        XMLPlatformUtils::Initialize();
    }

public:
    xml_string() = default;
    xml_string(const char* str) : _value(str) {
        _xml_value = XMLString::transcode(str);
    }

    xml_string(string str) : _value(str) {
        _xml_value = XMLString::transcode(str.c_str());
    }
    xml_string(const XMLCh* xmlch) : _xml_value(xmlch) {
        _value = XMLString::transcode(xmlch);
    }

    ~xml_string() {
        XMLPlatformUtils::Terminate();
    }

    bool operator==(const xml_string& rhs) {
        return XMLString::compareString(*this, rhs);
    }

    bool operator==(const char* rhs) {
        return _value.c_str() == rhs;
    }

    bool operator==(const char* rhs) const {
        return _value.c_str() == rhs;
    }

    operator string& () {
        return _value;
    }

    operator const XMLCh* () {
        return _xml_value;
    }

    operator XMLCh* () const {
        return const_cast<XMLCh*>(_xml_value);
    }

    bool empty() const {
        return _value.empty();
    }
};