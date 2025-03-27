#include "pch.h"
class treeview;

treeview_item::treeview_item(HTREEITEM item, treeview* owner) :
    ihandle(item), 
    m_treeview(owner)
{}

treeview_item::treeview_item(treeview_item&& other) noexcept :
    ihandle((ihandle&&)other),
    m_treeview(std::move(other.m_treeview))
   {}

bool treeview_item::is_root() const noexcept
{
    return this->get_parent().get_handle() == nullptr;
}

std::wstring treeview_item::get_text() const
{
    wchar_t buf[MAX_PATH];
    TVITEMEXW tvi{};
    tvi.hItem = *this;
    tvi.mask = TVIF_TEXT;
    tvi.cchTextMax = ARRAYSIZE(buf);
    tvi.pszText = buf;

    TreeView_GetItem(*m_treeview, &tvi);
    return tvi.pszText;
}

treeview_item& treeview_item::set_text(const wchar_t* text) noexcept
{
    TVITEMEXW tvi{};
    tvi.hItem = *this;
    tvi.mask = TVIF_TEXT;
    tvi.pszText = const_cast<wchar_t*>(text);

    TreeView_SetItem(*m_treeview, &tvi);
    return *this;
}

treeview_item& treeview_item::set_text(const std::wstring& text) noexcept
{
    return this->set_text(text.c_str());
}

treeview_item& treeview_item::set_selected() noexcept
{
    TreeView_SelectItem(*m_treeview, get_handle());
    return *this;
}

int treeview_item::get_icon_index() const noexcept
{
    TVITEMEXW tvi{};
    tvi.hItem = *this;
    tvi.mask = TVIF_IMAGE;

    TreeView_GetItem(*m_treeview, &tvi);
    return tvi.iImage;
}

treeview_item& treeview_item::set_icon_index(int ilIconIndex) noexcept
{
    TVITEMEXW tvi{};
    tvi.hItem = *this;
    tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
    tvi.iImage = ilIconIndex;
    tvi.iSelectedImage = ilIconIndex;

    TreeView_SetItem(*m_treeview, &tvi);
    return *this;
}

LPARAM treeview_item::get_lparam() const noexcept
{
    TVITEMEXW tvi{};
    tvi.hItem = *this;
    tvi.mask = TVIF_PARAM;

    TreeView_GetItem(*m_treeview, &tvi);
    return tvi.lParam;
}

treeview_item& treeview_item::set_lparam(LPARAM lParam)
{
    TVITEMEXW tvi{};
    tvi.hItem = *this;
    tvi.mask = TVIF_PARAM;
    tvi.lParam = lParam;

    TreeView_SetItem(*m_treeview, &tvi);
    return *this;
}

treeview_item& treeview_item::set_parent(treeview_item* parent)
{
       return *this;
}

treeview_item treeview_item::get_parent() const
{
    return 
    { 
        TreeView_GetParent(*m_treeview, get_handle()), 
        m_treeview 
    };
}

treeview_item treeview_item::get_first_child() const noexcept
{
    return
    {
        TreeView_GetChild(*m_treeview, get_handle()),
        m_treeview
    };
}

std::vector<treeview_item> treeview_item::get_children() const
{
    std::vector<treeview_item> children;
    treeview_item curIt = get_first_child();
    while (curIt.get_handle())
    {
        children.emplace_back(curIt);
        curIt = curIt.get_next_sibling();
    }
    return children;
}

treeview_item treeview_item::get_next_sibling() const noexcept
{
    return
    {
        TreeView_GetNextSibling(*m_treeview, get_handle()),
        m_treeview
    };
}

treeview_item treeview_item::add_child_with_icon(const wchar_t* text, int ilIconIndex) noexcept
{
    TVINSERTSTRUCTW tvi{};
    tvi.hParent = *this;
    tvi.hInsertAfter = TVI_LAST;
    tvi.itemex.mask = TVIF_TEXT | (ilIconIndex == -1 ? 0 : (TVIF_IMAGE | TVIF_SELECTEDIMAGE));
    tvi.itemex.pszText = const_cast<wchar_t*>(text);
    tvi.itemex.iImage = ilIconIndex;
    tvi.itemex.iSelectedImage = ilIconIndex;

    return 
    { 
        TreeView_InsertItem(*m_treeview, &tvi),
        m_treeview 
    };
}

treeview_item treeview_item::add_child_with_icon(const std::wstring& caption, int ilIconIndex) noexcept
{
    return this->add_child_with_icon(caption.c_str(), ilIconIndex);
}

treeview_item treeview_item::add_child(const wchar_t* caption) noexcept
{
    return this->add_child_with_icon(caption, -1);
}

treeview_item treeview_item::add_child(const std::wstring& caption) noexcept
{
    return this->add_child_with_icon(caption, -1);
}

