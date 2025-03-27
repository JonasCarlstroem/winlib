#pragma once

namespace nat
{
    class base_window : protected base_control
    {
    public:
        base_window();
        base_window(const base_config& cfg);
        base_window(const rect& bounds);
        base_window(int x, int y, int width, int height);
        base_window(base_window* parent, const base_config& cfg);
        base_window(base_window* parent, const rect& bounds);
        base_window(base_window* parent, int x, int y, int width, int height);
        base_window(base_window* parent, const rect& bounds, int x, int y, int width, int height);
        virtual ~base_window();

        HRESULT show(int nCmdShow);
        void add_control(base_control* ctrl);

        rect& get_window_size() const;
        rect& get_client_size() const;

        virtual LRESULT on_receive_message(UINT msg, WPARAM wParam, LPARAM lParam) override;

    protected:
        virtual BOOL custom_class() const { return TRUE; }
        virtual BOOL custom_window() const { return TRUE; }
        virtual BOOL custom_control() const { return FALSE; }
        virtual BOOL sub_class() const { return FALSE; }

        virtual LPCTSTR class_name() const = 0;
        virtual LPCTSTR menu_name() const { return NULL; }
        virtual LPCTSTR window_name() const = 0;
        virtual LONG window_style() const override;

        std::vector<base_control*>   m_controls;
    };
}