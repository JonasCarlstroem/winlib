#pragma once

namespace nat
{
    class icon
    {
    private:
        static std::vector<HICON>   m_loadedIcons;
        HICON                       m_hicon;

        icon(HICON icon) : m_hicon(icon) {}

        inline static HICON load(std::wstring name, int width, int height, UINT type)
        {
            return (HICON)::LoadImage(NULL, name.c_str(), IMAGE_ICON, width, height, type);
        }

    public:
        inline static icon load(std::wstring name)
        {
            HICON hicon = load(name, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR);
            m_loadedIcons.push_back(hicon);

            icon res(hicon);
            return res;
        }

        inline static icon load(std::wstring name, int width, int height)
        {
            HICON hicon;
            if (width == 0 && height == 0)
            {
                hicon = load(name, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR);
            }
            else
            {
                hicon = load(name, width, height, LR_DEFAULTCOLOR);
            }

            m_loadedIcons.push_back(hicon);

            icon res(hicon);
            return res;
        }

        inline static icon load(SHSTOCKICONID shIconId)
        {
            SHSTOCKICONINFO sico;
            sico.cbSize = sizeof(SHSTOCKICONINFO);
            UINT flags = SHGSI_ICON | SHGSI_LARGEICON;
            HRESULT hr = SHGetStockIconInfo(shIconId, flags, &sico);

            if (hr != S_OK)
            {
                hr = __HRESULT_FROM_WIN32(GetLastError());
            }

            m_loadedIcons.push_back(sico.hIcon);
            icon res(sico.hIcon);
            return res;
        }

        operator HICON()
        {
            return m_hicon;
        }
    };
}