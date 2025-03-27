#pragma once
#pragma comment(lib, "comctl32")

namespace nat
{
    class control : public base_control
    {
    public:
        control() : base_control() {}
        control(base_config cfg) : base_control(cfg) {}
        control(ihandle* hParent) : base_control(hParent) {}
        control(ihandle* parent, base_config cfg) : base_control(parent, cfg) {}
        control(ihandle* parent, int x, int y, int width, int height) : base_control(parent, x, y, width, height) {}

        //HWND Window() const { return m_hwnd; }

        void set_left(LONG left)
        {
            m_config.bounds.left = left;
        }

    protected:
        HRESULT set_rect(const CREATESTRUCT& create);
        //virtual HRESULT Create() override;

        virtual BOOL custom_class() const { return FALSE; }
        virtual BOOL custom_window() const final { return FALSE; }
        virtual BOOL custom_control() const final { return TRUE; }
        virtual BOOL sub_class() const { return FALSE; }

        virtual void on_before_create(CREATESTRUCT* create) override;
        static BOOL register_comctrl(DWORD ctrl);
    };

    HINSTANCE   get_instance();
    HBITMAP     set_bitmap_img(HINSTANCE hInst, WORD nID, HWND hwnd);
}