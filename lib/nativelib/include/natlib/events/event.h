#pragma once

namespace nat
{
    class event
    {
    public:
        virtual ~event() {};

        using descriptor_type = const char*;
        using window_message = UINT;

        virtual descriptor_type type() const = 0;
        virtual window_message message() const = 0;
    };

    class window_event : public event
    {
    public:
        UINT    uMsg;
        WPARAM  wParam;
        LPARAM  lParam;

        window_event(UINT umsg, WPARAM wparam, LPARAM lparam) :
            uMsg(umsg),
            wParam(wparam),
            lParam(lparam)
        {}
    };
}