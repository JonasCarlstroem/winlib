#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

using namespace std;

typedef function<void()> handler;
typedef unordered_map<string, handler> handlers;

namespace comp {
    class ui_element {
    protected:
        string id;
        handlers event_handlers;

    public:
        explicit ui_element(const string& elId) : id(elId) {}

        string get_id() const { return id; }

        void on(const string& evName, handler evHandler) {
            event_handlers[evName] = evHandler;
        }

        void fire(const string& evName) {
            if (event_handlers.find(evName) != event_handlers.end()) {
                event_handlers[evName]();
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