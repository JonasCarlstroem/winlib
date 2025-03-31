#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

using namespace std;

typedef function<void()> handler;
typedef unordered_map<string, handler> handlers;
typedef unordered_map<string, string> attribute_list;

namespace comp {
    class ui_element {
    protected:
        string _id;
        string _type;
        attribute_list _attributes;
        vector<ui_element*> _children;
        handlers _event_handlers;

    public:
        ui_element() : _id(""), _event_handlers() {}
        explicit ui_element(const string& elId) : _id(elId) {}

        string& id() { return _id; }
        string& type() { return _type; }

        void set_attribute(string name, string value) {
            _attributes[name] = value;
        }

        void add_child(ui_element* child) {
            for (const auto& el : _children) {
                if (el == child) return;
            }

            _children.push_back(child);
        }

        vector<ui_element*> get_children() { return _children; }
        attribute_list get_attributes() { return _attributes; }

        void on(const string& evName, handler evHandler) {
            _event_handlers[evName] = evHandler;
        }

        void fire(const string& evName) {
            if (_event_handlers.find(evName) != _event_handlers.end()) {
                _event_handlers[evName]();
            }
        }
    };

    typedef unordered_map<string, shared_ptr<ui_element>> ui_element_registry;
    ui_element_registry ui_registry;

    void register_ui_element(const string& id, shared_ptr<ui_element> el) {
        ui_registry[id] = el;
    }

    shared_ptr<ui_element> find_ui_element(const string& id) {
        auto it = ui_registry.find(id);
        if (it != ui_registry.end()) {
            return it->second;
        }
        return nullptr;
    }
}