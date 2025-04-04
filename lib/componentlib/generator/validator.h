#pragma once
#include <string>
#include <vector>
#include "types.h"
#include "xml_char_map.h"
#include "xsd_schema.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;
using namespace std;

class validator {
private:
    XercesDOMParser* _parser;

public:
    validator() : _parser(nullptr) {
        _parser = new XercesDOMParser();
        _parser->setValidationScheme(XercesDOMParser::Val_Always);
        _parser->setDoNamespaces(true);
        _parser->setDoSchema(true);
    }

    xsd_schema parse(const string& file) {

    }
    //DOMDocument* parse_schema(const string& filename) {
    //    DOMDocument* doc;

    //    try {
    //        _parser->parse(filename.c_str());
    //        doc = _parser->getDocument();
    //        DOMNode* schema_node = doc->getFirstChild();
    //        xs_schema* sc = get_schema(schema_node);
    //        if (XMLString::compareString(schema_node->getNodeName(), XS_SCHEMA)) {
    //            DOMNamedNodeMap* attributes = schema_node->getAttributes();
    //            const char* attrName = "elementFormDefault";
    //            DOMNode* attribute = attributes->getNamedItem(XMLString::transcode(attrName));

    //            if (attribute != nullptr) {

    //            }

    //            const XMLCh* elFormDef = attribute->getNodeName();
    //            const char* test = XMLString::transcode(elFormDef);
    //            const char* a = "hej";
    //        }
    //        const XMLCh* local_name = schema_node->getLocalName();
    //        const XMLCh* schema_name = schema_node->getNodeName();
    //        
    //        return doc;
    //    }
    //    catch (const XMLException& e) {
    //        return nullptr;
    //    }

    //    //if (doc != nullptr) return doc;

    //    throw exception("Error: could not parse file");
    //}

    //xs_schema* get_schema(DOMNode* schema_node) {
    //    DOMNamedNodeMap* schema_attributes = schema_node->getAttributes();
    //    xs_schema* sch = new xs_schema(schema_node);

    //    if (schema_attributes != nullptr) {
    //        
    //    }

    //    return sch;
    //}
};

const xml_string TYPE = xml_string("type");
const xml_string NAME = xml_string("name");
const xml_string USE = xml_string("use");

xsd_attribute parse_attribute(DOMElement* xml) {
    xsd_attribute attr;

    attr.name = xml->getAttribute(NAME);
    attr.type = to_type_ref(xml->getAttribute(TYPE));

    xml_string use = xml->getAttribute(USE);
    attr.is_required = (use == "required");

    return attr;
}

xsd_element parse_element(DOMElement* xml) {
    xsd_element el;
    el.name = xml->getAttribute(TYPE);

    if (xml->hasAttribute(TYPE)) {
        el.type = to_type_ref(xml->getAttribute(TYPE));
    }
    else {
        DOMNodeList* el_children = xml->getChildNodes();
        for (XMLSize_t i = 0; i < el_children->getLength(); ++i) {

        }
    }

    el.type = to_type_ref(xml->getAttribute(xml_string("type")));

    xml_string minOccurs = xml->getAttribute(xml_string("minOccurs"));
    xml_string maxOccurs = xml->getAttribute(xml_string("maxOccurs"));
    
    if (!minOccurs.empty()) el.min_occurs = stoi(minOccurs);
    if (!maxOccurs.empty()) {
        if (maxOccurs == "unbounded") {
            el.max_occurs = -1;
            el.is_array = true;
        }
        else {
            el.max_occurs = stoi(maxOccurs);
            el.is_array = el.max_occurs > 1;
        }
    }

    el.is_optional = (el.min_occurs == 0);

    return el;
}

void parse_sequence(xsd_complex_type* complex_type, DOMElement* xml) {
    DOMNodeList* seq_children = xml->getChildNodes();
    for (XMLSize_t i = 0; i < seq_children->getLength(); ++i) {
        DOMNode* seq_node = seq_children->item(i);

        if (seq_node->getNodeType() != DOMNode::ELEMENT_NODE) continue;

        DOMElement* seq_el = dynamic_cast<DOMElement*>(seq_node);
        if (seq_el->getTagName() == xml_string("xs:element")) {
            xsd_element instance = parse_element(seq_el);
            complex_type->sequence.push_back(instance);
        }
    }
}

xsd_complex_type parse_complex_type(DOMElement* xml) {
    xsd_complex_type complex;
    complex.name = xml_string(xml->getAttribute(xml_string("name")));

    DOMNodeList* complex_children = xml->getChildNodes();
    for (XMLSize_t i = 0; i < complex_children->getLength(); ++i) {
        DOMNode* child_node = complex_children->item(i);
        if (child_node->getNodeType() != DOMNode::ELEMENT_NODE) continue;

        DOMElement* child_el = dynamic_cast<DOMElement*>(child_node);
        xml_string child_tag = child_el->getTagName();

        if (child_tag == "xs:sequence") {
            parse_sequence(&complex, child_el);
        }
        else if (child_tag == "xs:attribute") {

        }
    }
}

xsd_schema parse_schema_definition(const string& file) {
    XercesDOMParser parser;
    parser.parse(file.c_str());
    DOMDocument* doc = parser.getDocument();
    DOMElement* root = doc->getDocumentElement();

    xsd_schema schema;
    if (root->hasAttribute(xml_string("targetNamespace"))) {
        schema.target_namespace = xml_string(root->getAttribute(xml_string("targetNamespace")));
    }

    DOMNodeList* children = root->getChildNodes();
    for (XMLSize_t i = 0; i < children->getLength(); ++i) {
        DOMNode* node = children->item(i);
        if (node->getNodeType() != DOMNode::ELEMENT_NODE) continue;

        DOMElement* elem = dynamic_cast<DOMElement*>(node);
        xml_string tag = elem->getTagName();

        if (tag == "xs:complexType") {
            xsd_complex_type ct = parse_complex_type(elem);
        }
        else if (tag == "xs:element") {
            xsd_element el = parse_element(elem);
        }
    }
}

void parse_attribute_group_definition(DOMElement* el, xsd_schema& schema) {
    //xml_string name = 
}