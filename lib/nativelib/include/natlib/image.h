#pragma once

namespace nat
{
    class image
    {
    private:
        HBITMAP     m_bitmap;
        image(HBITMAP hbm) : m_bitmap(hbm) {};

        inline static HBITMAP load(std::wstring name, int width, int height, UINT type)
        {
            if (type < 1) type = LR_DEFAULTSIZE | LR_DEFAULTCOLOR;

            return (HBITMAP)::LoadImage(NULL, name.c_str(), IMAGE_BITMAP, width, height, type);
        }

        //inline static HBITMAP load_from_file(std::wstring fileName, int width, int height)
        //{

        //}
    };
}