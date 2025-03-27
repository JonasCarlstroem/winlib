#include "pch.h"

base_control::base_control() : 
    ihandle(0),
    m_parent(nullptr),
    m_config{},
    m_registered(false),
    m_originalWndProc(nullptr)
{}

base_control::base_control(const base_config& cfg) :
    ihandle(0),
    m_parent(nullptr),
    m_config{ cfg },
    m_registered(false),
    m_originalWndProc(nullptr)
{}

base_control::base_control(ihandle* parent) : 
    ihandle(0),
    m_parent(parent),
    m_config{},
    m_registered(false),
    m_originalWndProc(nullptr)
{}

base_control::base_control(ihandle* parent, const base_config& cfg) :
    ihandle(0),
    m_parent(parent),
    m_config{ cfg },
    m_registered(false),
    m_originalWndProc(nullptr)
{}

base_control::base_control(ihandle* parent, const rect& bounds) :  
    ihandle(0),
    m_parent(parent),
    m_config{ bounds },
    m_registered(false),
    m_originalWndProc(nullptr)
{}

base_control::base_control(ihandle* parent, int x, int y, int width, int height) : 
    ihandle(0),
    m_parent(parent),
    m_config{ {} },
    m_registered(false),
    m_originalWndProc(nullptr)
{
    m_config.set_x(x);
    m_config.set_y(y);
    m_config.set_width(width);
    m_config.set_height(height);
}

base_control::base_control(ihandle* parent, const rect& bounds, int x, int y, int width, int height) :
    ihandle(0),
    m_parent(parent),
    m_config{ bounds },
    m_registered(false),
    m_originalWndProc(nullptr)
{
    m_config.set_x(x);
    m_config.set_y(y);
    m_config.set_width(width);
    m_config.set_height(height);
}

void base_control::enable(BOOL bEnable)
{
    if (!bEnable && *this == GetFocus())
    {
        ::SendMessage(GetParent(*this), WM_NEXTDLGCTL, 0, FALSE);
    }

    EnableWindow(*this, bEnable);
}

LRESULT base_control::SendWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam) const
{
    return ::SendMessage(*this, msg, wParam, lParam);
}

bool base_control::has_style(LONG style) const
{
    return (GetWindowLong(*this, GWL_STYLE) & style) == style;
}

 LONG base_control::add_style(LONG style)
{
    LONG old_style = GetWindowLong(*this, GWL_STYLE);
    return SetWindowLong(*this, GWL_STYLE, old_style | style);
}

 LONG base_control::remove_style(LONG style)
{
    LONG old_style = GetWindowLong(*this, GWL_STYLE);
    old_style = old_style & (~style);
    return SetWindowLong(*this, GWL_STYLE, old_style);
}

 LONG base_control::enable_style(bool bEnable, LONG style)
{
    return (bEnable ? add_style(style) : remove_style(style));
}

HRESULT base_control::register_control()
{
    if (!m_registered)
    {
        if (custom_class())
        {
            WNDCLASSEXW wcex = { 0 };

            if (custom_control())
            {
                LPCTSTR subclsname = sub_class_name();

                GetClassInfoExW(NULL, sub_class_name(), &wcex);
                m_originalWndProc = wcex.lpfnWndProc;

                wcex.style &= ~CS_GLOBALCLASS;
            }
            else if (custom_window())
            {
                wcex.style = sub_class_style();
                wcex.cbClsExtra = 0;
                wcex.cbWndExtra = 0;
                wcex.hIcon = NULL;
                wcex.hCursor = get_cursor();
                //wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
                wcex.hbrBackground = get_bk_color().get_brush();
                wcex.lpszMenuName = menu_name();
                wcex.hIconSm = NULL;
            }

            wcex.cbSize = sizeof(WNDCLASSEXW);
            wcex.lpszClassName = class_name();
            wcex.hInstance = (HINSTANCE)*this;
            wcex.lpfnWndProc = base_control::wnd_proc;
            ATOM a = RegisterClassExW(&wcex);

            if (a == 0)
            {
                return __HRESULT_FROM_WIN32(GetLastError());
            }
            else
            {
                m_registered = true;
            }
        }
        else
        {
            m_registered = true;
        }
    }
    
    return m_registered ? S_OK : E_FAIL;
}

HRESULT base_control::create()
{
    CREATESTRUCT createStr;
    ZeroMemory(&createStr, sizeof(CREATESTRUCT));

    createStr.hwndParent = nullptr;
    return create(&createStr);
}

HRESULT base_control::create(CREATESTRUCT* create)
{
    if (m_parent != nullptr)
    {
        create->hwndParent = m_parent->get_handle<HWND>();
    }

    create->x = m_config.bounds.left;
    create->y = m_config.bounds.top;
    create->cx = m_config.bounds.right - create->x;
    create->cy = m_config.bounds.bottom - create->y;

    create->lpszName = window_name();
    create->lpszClass = class_name();
    create->style = window_style();
    create->dwExStyle = window_style_ex();

    if (get_handle() != NULL)
    {
       return E_FAIL;
    }
    
    if (get_instance() == NULL)
    {
        set_instance();
        if (get_instance() == NULL)
        {
            return E_INVALIDARG;
        }
    }

    HRESULT hr = register_control();
    if (SUCCEEDED(hr))
    {
        create->hInstance = get_instance();
        create->lpCreateParams = this;
        
        on_before_create(create);

        HWND hwnd = CreateWindowExW(create->dwExStyle,
                                          create->lpszClass,
                                          create->lpszName,
                                          create->style,
                                          m_config.get_x(), m_config.get_y(),
                                          m_config.get_width(), m_config.get_height(),
                                          create->hwndParent,
                                          create->hMenu,
                                          create->hInstance,
                                          create->lpCreateParams);

        if (!set_handle(hwnd))
        {
            return __HRESULT_FROM_WIN32(GetLastError());
        }

        if (sub_class())
        {
            //_SetWindowLongPtr(hwnd, GWLP_WNDPROC, wnd_proc);
        }

        on_created(created_event());
    }
    
    
    return hr;
}

LRESULT base_control::on_receive_message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_NCDESTROY:
        {
            SetWindowLongPtr(*this, GWLP_USERDATA, 0);
            return DefWindowProc(*this, uMsg, wParam, lParam);
        }
        case WM_INITDIALOG: 
        {
            return on_init_dialog(init_dialog_event(wParam, lParam));
            //break;
        }
        case WM_CREATE:
        {
            return on_create(create_event(wParam, lParam));
            //return 0;
        }
        case WM_PAINT:
        {
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(*this, &ps);

            //EndPaint(*this, &ps);
            //return 0;
            return on_paint(paint_event(*this, wParam, lParam));
        }
        case NM_CUSTOMDRAW:
        {
            return on_init_dialog(init_dialog_event(wParam, lParam));
        }
        case WM_NOTIFY:
        {
            switch (((LPNMHDR)lParam)->code)
            {
                case NM_FIRST:
                {
                    break;
                }
                case NM_CUSTOMDRAW:
                {
                    custom_draw_event ev(wParam, lParam);
                    switch (ev.draw_stage())
                    {
                        case CDDS_POSTERASE: return on_custom_draw_post_erase(ev);
                        case CDDS_POSTPAINT: return on_custom_draw_post_paint(ev);
                        case CDDS_PREERASE: return on_custom_draw_pre_erase(ev);
                        case CDDS_PREPAINT: return on_custom_draw_pre_paint(ev);

                        case CDDS_ITEM: return on_custom_draw_item(ev);
                        case CDDS_ITEMPOSTERASE: return on_custom_draw_item_post_erase(ev);
                        case CDDS_ITEMPOSTPAINT: return on_custom_draw_item_post_paint(ev);
                        case CDDS_ITEMPREERASE: return on_custom_draw_item_pre_erase(ev);
                        case CDDS_ITEMPREPAINT: return on_custom_draw_item_pre_paint(ev);
                        case CDDS_SUBITEM: return on_custom_draw_sub_item(ev);
                    }

                    return on_custom_draw(custom_draw_event(wParam, lParam));
                }
            }

            return on_notify(notify_event(wParam, lParam));
        }
    }

    if (sub_class())
    {
        return DefSubclassProc(*this, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(*this, uMsg, wParam, lParam);
    }
}

LRESULT CALLBACK base_control::wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    base_control* pCtrl = nullptr;

    if (uMsg == WM_NCCREATE)
    {
        LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
        pCtrl = (base_control*)lpcs->lpCreateParams;

        pCtrl->set_window(hwnd);

        _SetWindowLongPtr(hwnd, GWLP_USERDATA, pCtrl);
    }
    else
    {
        pCtrl = _GetWindowLongPtr<base_control*>(hwnd, GWLP_USERDATA);
    }

    if (pCtrl)
    {
        return pCtrl->on_receive_message(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void base_control::set_window(HWND& hwnd)
{
    set_handle(hwnd);
}

void base_control::set_bk_color(base_color clr)
{
    m_config.bkColor = clr;
}

base_color& base_control::get_bk_color()
{
    return m_config.bkColor;
}

void base_control::set_text_color(base_color clr)
{
    m_config.txtColor = clr;
}

base_color& base_control::get_text_color()
{
    return m_config.txtColor;
}

HCURSOR base_control::get_cursor() const
{
    static HCURSOR h = LoadCursor(NULL, cursor());
    return h;
}

LPCTSTR base_control::get_type_name() const
{
    const char* name = typeid(this).name();
    size_t len = strlen(name);
    wchar_t v[512];
    size_t ct = 0;
    mbstowcs_s(&ct, v, name, len);

    return v;
}

LRESULT base_control::on_init_dialog(const init_dialog_event& ev) 
{ 
    return on_def_wnd_proc(ev); 
}

LRESULT base_control::on_create(const create_event& ev) 
{ 
    return on_def_wnd_proc(ev); 
}

LRESULT base_control::on_paint(const paint_event& ev) 
{ 
    return on_def_wnd_proc(ev); 
}

LRESULT base_control::on_notify(const notify_event& ev) 
{ 
    return on_def_wnd_proc(ev); 
}

LRESULT base_control::on_custom_draw(const custom_draw_event& ev) 
{ 
    return on_def_wnd_proc(ev); 
}

LRESULT base_control::on_custom_draw_post_erase(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_post_paint(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_pre_erase(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_pre_paint(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_item(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_item_post_erase(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_item_post_paint(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_item_pre_erase(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_item_pre_paint(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_custom_draw_sub_item(const custom_draw_event& ev)
{
    //return on_def_wnd_proc(ev);
    return CDRF_DODEFAULT;
}

LRESULT base_control::on_def_wnd_proc(const window_event& ev)
{
    const auto& [uMsg, wParam, lParam] = ev;
    return DefWindowProc(*this, uMsg, wParam, lParam);
}