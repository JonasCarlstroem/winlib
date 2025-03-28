#include "pch.h"

namespace comp {
    bool treeview::m_bRegistered = false;

    treeview::treeview(base_control* parent) :
        control(parent) {
        register_control();
    }

    treeview::treeview(base_control* parent, int x, int y, int width, int height) :
        control(parent, x, y, width, height) {
        register_control();
    }

    treeview::treeview(base_control* parent, const base_config& cfg) :
        control(parent, cfg) {
        register_control();
    }

    treeview::treeview(treeview&& tree) noexcept :
        control(std::move(tree.m_parent),
                std::move(tree.m_config)),
        count(std::exchange(tree.count, 0)),
        m_imageList(std::move(tree.m_imageList)) {}


    treeview_item treeview::add_root_item_with_icon(const wchar_t* text, int ilIconId) noexcept {
        TVINSERTSTRUCTW tvi{};
        tvi.hParent = TVI_ROOT;
        tvi.hInsertAfter = TVI_LAST;
        tvi.itemex.mask = TVIF_TEXT | (ilIconId == -1 ? 0 : (TVIF_IMAGE | TVIF_SELECTEDIMAGE));
        tvi.itemex.pszText = const_cast<wchar_t*>(text);
        tvi.itemex.iImage = ilIconId;
        tvi.itemex.iSelectedImage = ilIconId;

        return
        {
            TreeView_InsertItem(*this, &tvi),
            this
        };
    }

    treeview_item treeview::add_root_item_with_icon(const std::wstring& caption, int ilIconId) noexcept {
        return this->add_root_item_with_icon(caption.c_str(), ilIconId);
    }

    treeview_item treeview::add_root_item(const wchar_t* text) noexcept {
        return this->add_root_item_with_icon(text, -1);
    }

    treeview_item treeview::add_root_item(const std::wstring& caption) noexcept {
        return this->add_root_item_with_icon(caption, -1);
    }



    bool treeview::insert_item(const TVINSERTSTRUCTW& tvins, treeview_item* item) {
        HTREEITEM hitem = (HTREEITEM)SendWindowMessage(TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
        if (hitem == NULL)
            return false;

        return item->set_handle(hitem);
    }


    void treeview::set_item(const TVITEMW& item) {
        TreeView_SetItem(*this, &item);
    }

    std::wstring treeview::get_text() {
        std::wostringstream iss;
        iss << L"Text #" << count++ << std::endl;
        std::wstring isstr = iss.str();
        std::wstring str = L"text #" + count++;
        wchar_t* res = const_cast<wchar_t*>(isstr.c_str());
        return isstr;
    }

    HRESULT treeview::register_control() {
        if (!m_bRegistered) {
            m_bRegistered = register_comctrl(ICC_TREEVIEW_CLASSES);

            HRESULT hr = base_control::register_control();
            if (hr != S_OK) {
                return __HRESULT_FROM_WIN32(GetLastError());
            }
        }

        return S_OK;
    }

    HRESULT treeview::create() {
        HRESULT hr;
        if (initialize()) {
            hr = control::create();
        }
        else {
            hr = __HRESULT_FROM_WIN32(GetLastError());
        }

        return hr;
    }

    BOOL treeview::initialize() {
        if (m_imageList == nullptr) {
            m_imageList = new image_list(16, 16, 0);

            std::function<void(image_list*)> cb = std::bind(&treeview::on_image_list_initialize, this, std::placeholders::_1);
            m_imageList->on_initialize(cb);

            if (!m_imageList->initialize())
                return FALSE;
        }

        return TRUE;
    }

    void treeview::attach_imagelist() {
        TreeView_SetImageList((HWND)*this, (HIMAGELIST)*m_imageList, TVSIL_NORMAL);
    }

    int treeview::add_image(HBITMAP hbitmap) {
        return m_imageList->add_image(hbitmap);
    }

    int treeview::add_icon(HICON hicon) {
        return m_imageList->add_icon(hicon);
    }

    void treeview::set_bk_color(base_color c) {
        base_control::set_bk_color(c);
        m_prevbkColor = TreeView_SetBkColor(*this, c);

        m_imageList->set_bk_color(c);
    }

    void treeview::set_text_color(base_color c) {
        base_control::set_text_color(c);
        m_prevtxtColor = TreeView_SetTextColor(*this, c);
    }

    LRESULT treeview::on_init_dialog(const init_dialog_event& ev) {
        return base_control::on_init_dialog(ev);
    }
}