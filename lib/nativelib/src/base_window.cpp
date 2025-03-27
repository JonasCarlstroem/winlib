#include "pch.h"

base_window::base_window() 
    : base_window(nullptr, {}, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0)
{}

base_window::base_window(const base_config& cfg) :
    base_window(nullptr, cfg)
{}

base_window::base_window(const rect& bounds) 
    : base_window(nullptr, bounds, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0) 
{}

base_window::base_window(int x, int y, int width, int height) 
    : base_window(nullptr, {}, x ,y, width, height)
{}

base_window::base_window(base_window* parent, const base_config& cfg) :
    base_control(parent, cfg)
{}

base_window::base_window(base_window* parent, const rect& bounds) 
    : base_control(parent, bounds, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0)
{}

base_window::base_window(base_window* parent, int x, int y, int width, int height)
    : base_control(parent, x, y, width, height)
{}

base_window::base_window(base_window* parent, const rect& bounds, int x, int y, int width, int height)
    : base_control(parent, bounds, x, y, width, height)
{}

base_window::~base_window()
{}

HRESULT base_window::show(int nCmdShow)
{
    ShowWindow(*this, nCmdShow);
    UpdateWindow(*this);
    return S_OK;
}

void base_window::add_control(base_control* ctrl)
{
    for (base_control* existing : m_controls)
    {
        if (existing == ctrl) return;
    }

    m_controls.push_back(ctrl);
}

rect& base_window::get_window_size() const
{
    rect sz;
    if (!GetWindowRect(*this, &sz))
    {
        throw std::exception();
    }

    return sz;
}

rect& base_window::get_client_size() const
{
    rect sz;
    if (!GetClientRect(*this, &sz))
    {
        throw std::exception();
    }

    return sz;
}

LRESULT base_window::on_receive_message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return base_control::on_receive_message(uMsg, wParam, lParam);
        }

        default: 
        {
            return base_control::on_receive_message(uMsg, wParam, lParam);
        }
    }
}

LONG base_window::window_style() const
{
    return WS_OVERLAPPEDWINDOW;
}