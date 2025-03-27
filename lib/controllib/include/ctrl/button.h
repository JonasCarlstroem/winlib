#pragma once

namespace ctrl
{
    enum button_type
    {
        invalid,
        text,
        image
    };

    class button : public control
    {
    public:
        button(base_control* hParent);
        button(base_control* hParent, const TCHAR* szCaption, int x, int y, int width, int height);
        button(base_control* hParent, int nImgID, int x, int y, int width, int height);

        HRESULT create_text();
        //static Button* CreateText(BaseControl* hParent, const TCHAR* szCaption, int nID, Rect& rcBound);

        HRESULT create_bitmap();
        //static Button* CreateBitmap(BaseControl* hParent, int nImgID, int nID, Rect& rcBound);
        BOOL set_image(WORD nImgId);

        void set_check(int nCheck)
        {
            SendWindowMessage(BM_SETCHECK, (WPARAM)nCheck, 0L);
        }

        BOOL is_checked()
        {
            return SendWindowMessage(BM_GETCHECK, 0, 0) == BST_CHECKED;
        }

    private:
        button_type      m_btnType;
        const TCHAR* m_szCaption;

        int             m_nImgId;

    protected:
        virtual LPCWSTR class_name() const override
        {
            return TEXT("BUTTON");
        }

        virtual LPCWSTR window_name() const override
        {
            return m_szCaption;
        }

        virtual LONG window_style() const override
        {
            return BS_PUSHBUTTON | BS_FLAT;
        }
    };

    class text_button : public button
    {
    public:
        text_button(base_control* parent, const TCHAR* caption, int x, int y, int width, int height)
            : button(parent, caption, x, y, width, height)
        {}
    };
}