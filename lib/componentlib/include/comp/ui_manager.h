#include "ui_element.h"

namespace comp {
    class ui_manager {
    private:
        ui_element_registry registry;

    public:
        void register_element(const string& id, shared_ptr<ui_element> el) {
            registry[id] = el;
        }

        shared_ptr<ui_element> find_element(const string& id) {
            auto it = registry.find(id);
            return (it != registry.end()) ? it->second : nullptr;
        }
    } static manager;
}

//ui_manager manager;