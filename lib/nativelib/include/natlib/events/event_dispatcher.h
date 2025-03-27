#pragma once

namespace nat
{
    class event_dispatcher
    {
    public:
        using slot_type = std::function<void(const event&)>;

        void subscribe(const event::descriptor_type& descriptor, slot_type&& slot);
        void post(const event& ev) const;

    private:
        std::map<event::descriptor_type, std::vector<slot_type>> _observers;
        std::map<event::descriptor_type, std::vector<event_observer>> _obs;
    };
}