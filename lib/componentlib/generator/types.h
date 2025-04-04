#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "utils.h"
#include "xml_char_map.h"
//#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
//#include <xercesc/util/XMLString.hpp>

using namespace xercesc;
using namespace std;

typedef unordered_map<string, string> attribute_list;

struct tag {
protected:
    string          tag_name;
    attribute_list  attributes;
    vector<tag*>    children;

public:
    tag(string name, DOMNode* node) : 
        tag_name(name),
        attributes(),
        children() {
        parse_tag(node);
    }

    virtual ~tag() {}

    virtual string name() const {
        return tag_name;
    }

    virtual const XMLCh* xml_tag() {
        return XMLString::transcode(name().c_str());
    }

    void add_child(tag* child) {
        children.push_back(child);
    }

    const vector<tag*> get_children() const {
        return children;
    }

private:
    void parse_tag(DOMNode* node) {
        const auto& type = node->getNodeType();
        log_line("NodeType=", dom_node_type(type));
        log_line();

        if (!XMLString::compareString(node->getNodeName(), xml_tag())) {
            log_line("Parsing attributes...");
            _tab_.inc();

            parse_attributes(node->getAttributes());
            parse_children(node->getChildNodes());
            //DOMNodeList* children_ = node->getChildNodes();
        }
    }

    void parse_attributes(DOMNamedNodeMap* attributes_) {
        XMLSize_t count = attributes_->getLength();
        log_line("AttributeCount=", count);
        _tab_.inc();

        for (int i = 0; i < count; i++) {
            DOMNode* attribute = attributes_->item(i);
            const auto& node_type = attribute->getNodeType();
            log_line("Attribute type: ", dom_node_type(node_type));

            if (node_type == DOMNode::NodeType::ATTRIBUTE_NODE) {
                const auto& node_name = attribute->getNodeName();
                const auto& node_value = attribute->getNodeValue();
                string _node_name = XMLString::transcode(attribute->getNodeName());
                string _node_value = XMLString::transcode(attribute->getNodeValue());

                //log_line("");
                log_line(_node_name, "=", _node_value);
                attributes.insert({ _node_name, _node_value });
            }

            log_line("");
        }
        _tab_.dec();
    }

    void parse_children(DOMNodeList* children_) {
        XMLSize_t count = children_->getLength();
        log_line("Children count: ", count);
        _tab_.inc();

        for (int i = 0; i < count; i++) {
            DOMNode* child = children_->item(i);
            const auto& node_type = child->getNodeType();

            log_line("Child type: ", dom_node_type(node_type));
            if (node_type == DOMNode::NodeType::ELEMENT_NODE) {
                const auto& node_name = child->getNodeName();

                if (node_name == XS_SCHEMA) {

                }
                else if (node_name == XS_ATTRIBUTE_GROUP) {

                }
                else if (node_name == XS_ATTRIBUTE) {

                }
            }
            else if (node_type == DOMNode::NodeType::TEXT_NODE) {
                const auto& node_name = child->getNodeName();
                const auto& node_value = child->getNodeValue();
                cout << node_value;
            }
        }
    }
};

struct _xs_tag : protected tag {
    inline _xs_tag(string name, DOMNode* node) : 
        tag("xs:" + name, node) {}
};

struct _xs_attribute_group : _xs_tag {
    _xs_attribute_group(DOMNode* node) : _xs_tag("attributeGroup", node) {}

    string& name() {
        return attributes["name"];
    }
};

struct _xs_attribute : _xs_tag {
    _xs_attribute(DOMNode* node) : _xs_tag("attribute", node) {}

    string& name() {
        return attributes["name"];
    }

    string& type() {
        return attributes["type"];
    }

    string& use() {
        return attributes["use"];
    }
};

struct _xs_schema : _xs_tag {
    _xs_schema(DOMNode* schema_node) : _xs_tag("schema", schema_node) {}

    string& elementFormDefault() {
        return attributes["elementFormDefault"];
    }
};