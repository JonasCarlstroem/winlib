#pragma once

namespace nat
{
    class init_dialog_event : public window_event
    {
    public:
        init_dialog_event(WPARAM wparam, LPARAM lparam) :
            window_event(WM_INITDIALOG, wparam, lparam)
        {};

        virtual ~init_dialog_event() {};

        static constexpr descriptor_type descriptor = "init_dialog";
        static constexpr window_message wnd_message = WM_INITDIALOG;

        virtual descriptor_type type() const
        {
            return descriptor;
        }

        virtual window_message message() const
        {
            return wnd_message;
        }
    };

    class create_event : public window_event
    {
    public:
        create_event(WPARAM wparam, LPARAM lparam) :
            window_event(WM_CREATE, wparam, lparam)
        {};

        virtual ~create_event() {};

        static constexpr descriptor_type descriptor = "create";
        static constexpr window_message wnd_message = WM_CREATE;

        virtual descriptor_type type() const
        {
            return descriptor;
        }

        virtual window_message message() const
        {
            return wnd_message;
        }
    };

    class created_event : public event
    {
    public:
        created_event() {};

        virtual ~created_event() {};

        static constexpr descriptor_type descriptor = "created";
        static constexpr window_message wnd_message = NULL;

        virtual descriptor_type type() const
        {
            return descriptor;
        }

        virtual window_message message() const
        {
            return wnd_message;
        }
    };

    class paint_event : public window_event
    {
    public:
        HWND                window;
        const HDC& context;
        PAINTSTRUCT         paint_struct;

        paint_event(HWND hwnd, WPARAM wparam, LPARAM lparam) :
            window_event(WM_PAINT, wparam, lparam),
            window(hwnd),
            paint_struct(),
            context(BeginPaint(hwnd, &paint_struct))
        {};

        virtual ~paint_event()
        {
            EndPaint(window, &paint_struct);
        };

        static constexpr descriptor_type descriptor = "paint";
        static constexpr window_message wnd_message = WM_PAINT;

        virtual descriptor_type type() const
        {
            return descriptor;
        }

        virtual window_message message() const
        {
            return wnd_message;
        }

        const PAINTSTRUCT& ps() const
        {
            return paint_struct;
        }

        const HDC& hdc() const
        {
            return context;
        }
    };

    class notify_event : public window_event
    {
    public:
        notify_event(WPARAM wparam, LPARAM lparam) :
            window_event(WM_NOTIFY, wparam, lparam)
        {};

        virtual ~notify_event() {};

        static constexpr descriptor_type descriptor = "notify";
        static constexpr window_message wnd_message = WM_NOTIFY;

        virtual descriptor_type type() const
        {
            return descriptor;
        }

        virtual window_message message() const
        {
            return wnd_message;
        }
    };

    class custom_draw_event : public window_event
    {
    public:

        custom_draw_event(WPARAM wparam, LPARAM lparam) :
            window_event(NM_CUSTOMDRAW, wparam, lparam)
        {};

        virtual ~custom_draw_event() {};

        static constexpr descriptor_type descriptor = "custom_draw";
        static constexpr window_message wnd_message = NM_CUSTOMDRAW;

        virtual descriptor_type type() const
        {
            return descriptor;
        }

        virtual window_message message() const
        {
            return wnd_message;
        }

        LPNMCUSTOMDRAW custom_draw() const
        {
            return (LPNMCUSTOMDRAW)lParam;
        }

        LPNMLVCUSTOMDRAW custom_draw_list_view() const
        {
            return (LPNMLVCUSTOMDRAW)lParam;
        }

        LPNMTTCUSTOMDRAW custom_draw_tooltip() const
        {
            return (LPNMTTCUSTOMDRAW)lParam;
        }

        LPNMTVCUSTOMDRAW& custom_draw_treeview() const
        {
            return (LPNMTVCUSTOMDRAW&)lParam;
        }

        LPNMTBCUSTOMDRAW& custom_draw_toolbar() const
        {
            return (LPNMTBCUSTOMDRAW&)lParam;
        }

        DWORD& draw_stage() const
        {
            return custom_draw()->dwDrawStage;
        }

        HDC& hdc() const
        {
            return custom_draw()->hdc;
        }

        NMHDR& hdr() const
        {
            return custom_draw()->hdr;
        }

        LPARAM item_lParam() const
        {
            return custom_draw()->lItemlParam;
        }

        RECT& rect() const
        {
            return custom_draw()->rc;
        }

        UINT& item_state() const
        {
            return custom_draw()->uItemState;
        }

        operator LPNMCUSTOMDRAW() { return custom_draw(); }
        operator LPNMLVCUSTOMDRAW() { return (LPNMLVCUSTOMDRAW)custom_draw(); }
        operator LPNMTTCUSTOMDRAW() { return (LPNMTTCUSTOMDRAW)custom_draw(); }
        operator LPNMTVCUSTOMDRAW() { return (LPNMTVCUSTOMDRAW)custom_draw(); }
        operator LPNMTBCUSTOMDRAW() { return (LPNMTBCUSTOMDRAW)custom_draw(); }
        operator NMCUSTOMDRAW() { return *(LPNMCUSTOMDRAW)custom_draw(); }
        operator NMLVCUSTOMDRAW() { return (NMLVCUSTOMDRAW)*this; }
        operator NMTTCUSTOMDRAW() { return (NMTTCUSTOMDRAW)*this; }
        operator NMTVCUSTOMDRAW() { return (NMTVCUSTOMDRAW)*this; }
        operator NMTBCUSTOMDRAW() { return (NMTBCUSTOMDRAW)*this; }

        operator const LPNMCUSTOMDRAW() const { return custom_draw(); }
        operator const LPNMLVCUSTOMDRAW() const { return (LPNMLVCUSTOMDRAW)custom_draw(); }
        operator const LPNMTTCUSTOMDRAW() const { return (LPNMTTCUSTOMDRAW)custom_draw(); }
        operator const LPNMTVCUSTOMDRAW() const { return (LPNMTVCUSTOMDRAW)custom_draw(); }
        operator const LPNMTBCUSTOMDRAW() const { return (LPNMTBCUSTOMDRAW)custom_draw(); }
        operator const NMCUSTOMDRAW() const { return *(LPNMCUSTOMDRAW)custom_draw(); }
        operator const NMLVCUSTOMDRAW() const { return (NMLVCUSTOMDRAW)*this; }
        operator const NMTTCUSTOMDRAW() const { return (NMTTCUSTOMDRAW)*this; }
        operator const NMTVCUSTOMDRAW() const { return (NMTVCUSTOMDRAW)*this; }
        operator const NMTBCUSTOMDRAW() const { return (NMTBCUSTOMDRAW)*this; }
    };

}