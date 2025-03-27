#pragma once

namespace nat
{
    struct base_config
    {
        rect            bounds;
        int             width, height;

        base_color      bkColor;
        base_color      txtColor;

        const int& get_x() { return bounds.left; }
        void set_x(int x) { bounds.left = x; }
        const int& get_y() { return bounds.top; }
        void set_y(int y) { bounds.top = y; }

        const int& get_width() { return bounds.right - bounds.left; }
        void set_width(int width) { bounds.right = bounds.left + width; }
        const int& get_height() { return bounds.bottom - bounds.top; }
        void set_height(int height) { bounds.bottom = bounds.top + height; }
    };

    class base_control : public ihandle, public event_dispatcher
    {
    public:
        virtual void enable(BOOL bEnable);

        virtual LRESULT SendWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam) const;

        virtual bool has_style(LONG style) const;
        virtual LONG add_style(LONG style);
        virtual LONG remove_style(LONG style);
        virtual LONG enable_style(bool bEnable, LONG style);

        virtual HRESULT create();
        void set_window(HWND&);
        virtual void set_bk_color(base_color);
        base_color& get_bk_color();

        virtual void set_text_color(base_color);
        base_color& get_text_color();

        virtual const int& get_x() { return m_config.bounds.left; }
        virtual const int& get_y() { return m_config.bounds.top; }
        virtual const int& get_width() { return m_config.bounds.right - m_config.bounds.left; }
        virtual const int& get_height() { return m_config.bounds.bottom - m_config.bounds.top; }

        virtual void set_x(int x) { m_config.bounds.left = x; }
        virtual void set_y(int y) { m_config.bounds.top = y; }
        virtual void set_width(int width) { m_config.bounds.right = m_config.bounds.left + width; }
        virtual void set_height(int height) { m_config.bounds.bottom = m_config.bounds.top + height; }

        virtual void set_size(int width, int height)
        {
            m_config.bounds.right = m_config.bounds.left + width;
            m_config.bounds.bottom = m_config.bounds.top + height;
        }

        virtual void set_pos(int x, int y)
        {
            int width = get_width();
            int height = get_height();

            m_config.bounds.left = x;
            m_config.bounds.right = m_config.bounds.left + width;

            m_config.bounds.top = y;
            m_config.bounds.bottom = m_config.bounds.top + height;
        }

        virtual LRESULT on_receive_message(UINT, WPARAM, LPARAM);
        static LRESULT CALLBACK wnd_proc(HWND, UINT, WPARAM, LPARAM);

    protected:
        ihandle* m_parent;
        base_config             m_config;

        base_control();
        base_control(const base_config&);
        base_control(ihandle*);
        base_control(ihandle*, const base_config&);
        base_control(ihandle*, const rect&);
        base_control(ihandle*, int, int, int, int);
        base_control(ihandle*, const rect&, int, int, int, int);

        virtual HRESULT register_control();

        virtual BOOL custom_class() const = 0;
        virtual BOOL custom_window() const = 0;
        virtual BOOL custom_control() const = 0;
        virtual BOOL sub_class() const = 0;

        virtual LPCTSTR sub_class_name() const { return get_type_name(); }
        virtual UINT sub_class_style() const { return CS_HREDRAW | CS_VREDRAW; }

        virtual LPWSTR cursor() const { return IDC_ARROW; }
        virtual HCURSOR get_cursor() const;

        virtual LPCTSTR class_name() const = 0;
        virtual LPCTSTR window_name() const = 0;

        virtual LONG window_style() const { return 0; }

        virtual LPCTSTR menu_name() const { return NULL; }
        virtual DWORD window_style_ex() const { return NULL; }

        HRESULT create(CREATESTRUCT* create);

        virtual LRESULT on_init_dialog(const init_dialog_event& ev);
        virtual LRESULT on_create(const create_event& ev);
        virtual LRESULT on_paint(const paint_event& ev);
        virtual LRESULT on_notify(const notify_event& ev);

        virtual LRESULT on_custom_draw(const custom_draw_event& ev);

        virtual LRESULT on_custom_draw_post_erase(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_post_paint(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_pre_erase(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_pre_paint(const custom_draw_event& ev);

        virtual LRESULT on_custom_draw_item(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_item_post_erase(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_item_post_paint(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_item_pre_erase(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_item_pre_paint(const custom_draw_event& ev);
        virtual LRESULT on_custom_draw_sub_item(const custom_draw_event& ev);

        LRESULT on_def_wnd_proc(const window_event& ev);

        virtual void on_before_create(CREATESTRUCT* create) { return; }
        virtual void on_create(const CREATESTRUCT* create) { return; }
        virtual void on_created(const created_event& ev) { return; }

        operator HWND()
        {
            return get_handle<HWND>();
        }

        operator const HWND() const
        {
            return get_handle<HWND>();
        }

    private:
        BOOL                    m_registered;
        WNDPROC                 m_originalWndProc;
        event_dispatcher        m_listener;

        LPCTSTR get_type_name() const;
    };
}