#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

using namespace std;

typedef function<void()> handler;
typedef unordered_map<string, handler> handlers;

using attribute_list = unordered_map<string, string>;

class attrib_list {
private:
    unordered_map<string, const char*> _attributes;

public:
    void add(string key, string value) {
        _attributes[key] = value.c_str();
    }

    template<class T>
    T get(string key) {
        return reinterpret_cast<T>(_attributes[key]);
    }

    string operator[](string key) {
        return _attributes[key];
    }

    template<class T>
    T& operator[](string key) {
        return get<T>(key);
    }

    auto begin() {
        return _attributes.begin();
    }

    auto end() {
        return _attributes.end();
    }
};

namespace comp {
    class ui_element {
    protected:
        string  _id, _type;
        int     _width, _height;

        attrib_list _attributes;
        vector<ui_element*> _children;
        handlers _event_handlers;

    public:
        ui_element() : _id(""), _event_handlers() {}
        explicit ui_element(const string& elId) : _id(elId) {}

        string& id() { return _id; }
        string& type() { return _type; }
        int width() { return _attributes.get<int>("width"); }
        int height() { return _attributes.get<int>("height"); }

        void set_attribute(string name, string value, string def_val = "") {
            _attributes[name] = (value.empty() ? def_val : value);
        }

        void add_child(ui_element* child) {
            for (const auto& el : _children) {
                if (el == child) return;
            }

            _children.push_back(child);
        }

        vector<ui_element*> get_children() { return _children; }
        attrib_list get_attributes() { return _attributes; }

        void on(const string& evName, handler evHandler) {
            _event_handlers[evName] = evHandler;
        }

        void fire(const string& evName) {
            if (_event_handlers.find(evName) != _event_handlers.end()) {
                _event_handlers[evName]();
            }
        }
    };
}