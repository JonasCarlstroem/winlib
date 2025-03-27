#include "pch.h"

void event_dispatcher::subscribe(const event::descriptor_type& descriptor, slot_type&& slot)
{
    _observers[descriptor].push_back(slot);
}

void event_dispatcher::post(const event& ev) const
{
    auto type = ev.type();

    if (_observers.find(type) == _observers.end())
        return;

    auto&& observers = _observers.at(type);

    for (auto&& observer : observers)
    {
        observer(ev);
    }
}