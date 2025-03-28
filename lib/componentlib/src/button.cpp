#include "pch.h"

namespace comp {
    button::button(base_control* hParent)
        : control(hParent, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0),
        m_szCaption(L"Press"),
        m_nImgId(0),
        m_btnType(button_type::invalid) {}

    button::button(base_control* hParent, const TCHAR* szCaption, int x, int y, int width, int height)
        : control(hParent, x, y, width, height),
        m_szCaption(szCaption),
        m_nImgId(0),
        m_btnType(button_type::text) {}

    button::button(base_control* hParent, int nImgId, int x, int y, int width, int height)
        : control(hParent, x, y, width, height),
        m_szCaption(NULL),
        m_nImgId(nImgId),
        m_btnType(button_type::image) {}

    HRESULT button::create_text() {
        if (m_btnType == text) {
            return control::create();
            /*CREATESTRUCT create;
            ZeroMemory(&create, sizeof(CREATESTRUCT));

            create.x = m_rcBound->left;
            create.y = m_rcBound->top;
            create.cx = m_rcBound->right - create.x;
            create.cy = m_rcBound->bottom - create.y;

            create.hwndParent = m_hwndParent;
            create.lpszName = m_szCaption;
            create.hMenu = (HMENU)(INT_PTR)m_nID;
            create.lpszClass = TEXT("BUTTON");
            create.style = BS_PUSHBUTTON | BS_FLAT;

            return Control::Create(create);*/
        }

        return E_FAIL;
    }

    //Button* Button::CreateText(BaseControl* hParent, const TCHAR* szCaption, int nID, Rect& rcBound)
    //{
    //    Button* btn = new Button(hParent, szCaption, nID, rcBound);
    //    HRESULT hr = btn->CreateText();
    //
    //    if (hr == S_OK)
    //    {
    //        return btn;
    //    }
    //
    //    return nullptr;
    //}

    HRESULT button::create_bitmap() {
        if (m_btnType == image) {
            HRESULT hr = create_text();

            if (SUCCEEDED(hr)) {
                set_image((WORD)m_nImgId);
            }

            return hr;
        }

        return E_FAIL;
    }

    //Button* Button::CreateBitmap(BaseControl* hParent, int nImgID, int nID, Rect& rcBound)
    //{
    //    Button* btn = new Button(hParent, nImgID, nID, rcBound);
    //    HRESULT hr = btn->CreateBitmap();
    //
    //    if (SUCCEEDED(hr))
    //    {
    //        return btn;
    //    }
    //
    //    return nullptr;
    //}

    BOOL button::set_image(WORD nImgId) {
        add_style(BS_BITMAP);
        HBITMAP hBitmap = set_bitmap_img(get_instance(), nImgId, *this);
        return (hBitmap ? TRUE : FALSE);
    }
}