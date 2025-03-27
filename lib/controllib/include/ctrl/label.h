#pragma once

namespace ctrl
{
    class label : public control
    {
    public:
        label(ihandle* parent);
        label(ihandle* parent, const TCHAR* szText);
        label(ihandle* parent, const TCHAR* szText, int x, int y, int width, int height);

        HRESULT create_label();

    private:
        const TCHAR* m_szText;

        virtual LPCWSTR class_name() const override
        {
            return TEXT("STATIC");
        }

        virtual LPCWSTR window_name() const override
        {
            return m_szText;
        }
    };
}