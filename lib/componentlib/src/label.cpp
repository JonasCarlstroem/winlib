#include "pch.h"

namespace comp {
    label::label(ihandle* hParent)
        : control(hParent),
        m_szText(L"")
    {}

    label::label(ihandle* parent, const TCHAR* szText) 
        : control(parent),
        m_szText(szText)
    {}

    label::label(ihandle* hParent, const TCHAR* szText, int x, int y, int width, int height)
        : control(hParent, x, y, width, height),
        m_szText(szText)
    {}

    HRESULT label::create_label()
    {
        /*CREATESTRUCT create;
        ZeroMemory(&create, sizeof(CREATESTRUCT));

        create.x = m_rcBound->left;
        create.y = m_rcBound->top;*/
        return control::create();
    }
}