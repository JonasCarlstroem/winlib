#pragma once

namespace nat
{
    class ihandle
    {
    public:
        friend class control;
        friend class base_control;

        operator HINSTANCE()
        {
            return m_hinstance;
        }

        operator HANDLE()
        {
            return m_handle;
        }

        operator HINSTANCE() const
        {
            return m_hinstance;
        }

        operator const HANDLE() const
        {
            return m_handle;
        }

        HINSTANCE get_instance() const
        {
            return *this;
        }

        ihandle(ihandle&& other) :
            m_hinstance(std::move(other.m_hinstance)),
            m_handle(std::move(other.m_handle))
        {}

        ihandle(const ihandle& other) :
            m_hinstance(other.m_hinstance),
            m_handle(other.m_handle)
        {}

    private:
        static std::map<SHSTOCKICONID, HICON> m_loadedIcons;
        HINSTANCE m_hinstance;
        HANDLE m_handle;

    protected:

        ihandle(HANDLE handle) :
            ihandle(GetModuleHandle(NULL), handle)
        {}

        ihandle(HINSTANCE hinstance, HANDLE handle) :
            m_hinstance(hinstance),
            m_handle(handle)
        {}

        ihandle& operator=(const ihandle&& other)
        {
            m_hinstance = std::move(other.m_hinstance);
            m_handle = std::move(other.m_handle);
            return *this;
        }

        ihandle& operator=(const HANDLE& thandle)
        {
            m_handle = thandle;
            return *this;
        }

        ihandle& operator=(const HANDLE&& thandle)
        {
            m_handle = std::move(thandle);

            return *this;
        }

        void set_instance(HINSTANCE hinst = NULL)
        {
            if (m_hinstance == NULL && hinst == NULL)
            {
                hinst = GetModuleHandle(NULL);
            }

            m_hinstance = hinst;
        }

        HANDLE get_handle() const
        {
            return m_handle;
        }

        template<typename T>
        T get_handle() const
        {
            return (T)m_handle;
        }

        BOOL set_handle(const HANDLE& handle)
        {
            if (handle == nullptr || m_handle != NULL)
            {
                return FALSE;
            }

            m_handle = handle;
            return TRUE;
        }

        static void set_handle(ihandle* h, HANDLE& thandle)
        {
            h->m_handle = thandle;
        }

        HICON LoadIcon(LPCWSTR name)
        {
            return ::LoadIcon(*this, name);
        }

        HANDLE LoadImage(LPCWSTR name, UINT type, int cx, int cy, UINT fuLoad)
        {
            return ::LoadImage(*this, name, type, cx, cy, fuLoad);
        }

        HBITMAP GetBitmapFromIcon(HICON& icon)
        {
            ICONINFO iconinfo;
            GetIconInfo(icon, &iconinfo);

            return iconinfo.hbmMask;
        }

        HBITMAP GetIconAsBitmap(LPWSTR name)
        {
            HICON icon = LoadIcon(MAKEINTRESOURCE(name));

            return GetBitmapFromIcon(icon);
        }

        HICON GetStockIcon(SHSTOCKICONID id)
        {
            if (m_loadedIcons[id])
            {
                return m_loadedIcons[id];
            }

            SHSTOCKICONINFO sico;
            sico.cbSize = sizeof(SHSTOCKICONINFO);

            HRESULT hr = SHGetStockIconInfo(id, SHGSI_ICON, &sico);

            if (hr != S_OK)
            {
                hr = __HRESULT_FROM_WIN32(GetLastError());
            }

            m_loadedIcons.insert({ id, sico.hIcon });

            return sico.hIcon;
        }
    };

    std::map<SHSTOCKICONID, HICON> ihandle::m_loadedIcons;
}