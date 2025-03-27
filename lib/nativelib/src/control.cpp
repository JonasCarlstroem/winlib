#include "pch.h"

HRESULT control::set_rect(const CREATESTRUCT& create)
{
    return S_OK;
}

void control::on_before_create(CREATESTRUCT* create)
{
    create->style |= WS_CHILD | WS_VISIBLE;
}

BOOL control::register_comctrl(DWORD ctrl)
{
    InitCommonControls();
    //INITCOMMONCONTROLSEX init;

    //init.dwSize = sizeof(INITCOMMONCONTROLSEX);
    //init.dwICC = ctrl;

    //BOOL res = InitCommonControlsEx(&init);
    return TRUE;
}

HINSTANCE get_instance()
{
    return (HINSTANCE)GetModuleHandle(NULL);
}

HBITMAP set_bitmap_img(HINSTANCE hinst, WORD nImgId, HWND hwnd)
{
    HBITMAP hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(nImgId));
    if (hBitmap)
    {
        SendMessage(hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
        return hBitmap;
    }

    return 0;
}