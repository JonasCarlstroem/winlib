#pragma once

namespace nat
{
    template<typename T>
    class IHandler
    {
    private:
        void(T::* handler)();

    public:
        void set_handler(void(T::* func)())
        {
            handler = func;
        }
    };

    typedef std::map<HANDLE, int> image_index;

    class image_list : public ihandle
    {
    private:
        const HIMAGELIST& hImgl()
        {
            return *this;
        }

        int                 m_width;
        int                 m_height;
        UINT                m_flags = ILC_COLOR32;
        int                 m_initialSize;

        int                 m_imglisttype = TVSIL_NORMAL;
        base_color          m_bkColor;
        base_color          m_prevbkColor;

        static image_index  m_loadedimages;

        BOOL create_list()
        {
            HIMAGELIST list;
            if ((list = ImageList_Create(m_width,
                                         m_height,
                                         m_flags,
                                         m_initialSize,
                                         m_imglisttype)) == NULL)
            {
                return FALSE;
            }

            return set_handle(list);
        }

        std::function<void(image_list*)> _initCallback;
        base_control* _instance = nullptr;

    public:
        image_list() :
            image_list(32, 32)
        {}

        image_list(int width, int height) :
            image_list(width, height, 0)
        {}

        image_list(int width, int height, int initSize) :
            image_list(width, height, 0, false)
        {}

        image_list(int width, int height, int initSize, bool state) :
            ihandle(0),
            m_width(width),
            m_height(height),
            m_initialSize(initSize),
            m_imglisttype(state ? TVSIL_STATE : TVSIL_NORMAL)
        {}

        BOOL initialize()
        {
            if (create_list())
            {

                if (_initCallback != nullptr)
                {
                    _initCallback(this);
                }
            }

            return TRUE;
        }

        BOOL add(HBITMAP)
        {

        }

        int add_icon(HICON icon)
        {
            if (m_loadedimages.count(icon) > 0)
            {
                return m_loadedimages[icon];
            }

            int iconId = ImageList_AddIcon(*this, icon);

            m_loadedimages.insert({ icon, iconId });
            return iconId;
        }

        int add_icon(SHSTOCKICONID)
        {
            //HICON icon = 
            return 0;
        }

        int add_image(HBITMAP bitmap)
        {
            if (m_loadedimages.count(bitmap) > 0)
            {
                return m_loadedimages[bitmap];
            }

            int imageId = ImageList_Add(*this, bitmap, (HBITMAP)NULL);
            m_loadedimages.insert({ bitmap, imageId });
            return ImageList_Add(*this, bitmap, (HBITMAP)NULL);
        }

        int get_image_count()
        {
            return ImageList_GetImageCount(*this);
        }

        void set_bk_color(const base_color& clr)
        {
            m_bkColor = clr;
            m_prevbkColor = ImageList_SetBkColor(*this, m_bkColor);
        }

        void set_image_list(const HWND& hwnd)
        {
            TreeView_SetImageList(hwnd, *this, m_imglisttype);
        }

        void on_initialize(std::function<void(image_list*)> callback)
        {
            _initCallback = callback;
        }

        operator HIMAGELIST()
        {
            return get_handle<HIMAGELIST>();
        }
    };
}