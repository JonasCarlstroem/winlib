#pragma once

//class treeview;

namespace ctrl
{
    class treeview_item : public ihandle
    {
        friend treeview;

    protected:
        treeview* m_treeview;

    public:
        treeview_item(HTREEITEM hti, treeview* owner);
        treeview_item(treeview_item&& other) noexcept;
        treeview_item(const treeview_item&) = default;

        treeview_item& operator=(treeview_item&& other) noexcept
        {
            this->m_treeview = std::move(other.m_treeview);
            return *this;
        }

        operator HTREEITEM()
        {
            return get_handle<HTREEITEM>();
        }

        operator const HTREEITEM() const
        {
            return get_handle<HTREEITEM>();
        }

        bool is_root() const noexcept;
        treeview_item& set_parent(treeview_item* parent);
        treeview_item get_parent() const;

        treeview_item get_first_child() const noexcept;
        std::vector<treeview_item> get_children() const;
        treeview_item get_next_sibling() const noexcept;

        template<typename Ttreeview, typename Ttreeview_item, typename... Targs>
        Ttreeview_item add_child_with_icon(const std::wstring& text, int iconId, Targs... args)
        {
            static_assert(std::is_base_of<treeview, Ttreeview>::value, "Ttreeview must derive from type treeview");
            static_assert(std::is_base_of<treeview_item, Ttreeview_item>::value, "Ttreeview_item must derive from type treeview_item");
            TVINSERTSTRUCTW tvi{};

            tvi.hParent = *this;
            tvi.hInsertAfter = TVI_LAST;
            tvi.itemex.mask = TVIF_TEXT | (iconId == -1 ? 0 : (TVIF_IMAGE | TVIF_SELECTEDIMAGE));
            tvi.itemex.pszText = const_cast<wchar_t*>(text.data());
            tvi.itemex.iImage = iconId;
            tvi.itemex.iSelectedImage = iconId;

            return
            {
                TreeView_InsertItem(m_treeview->get_handle<HWND>(), &tvi),
                (Ttreeview*)m_treeview,
                args...
            };
        }

        treeview_item add_child_with_icon(const wchar_t*, int = -1) noexcept;
        treeview_item add_child_with_icon(const std::wstring&, int = -1) noexcept;
        treeview_item add_child(const wchar_t* caption) noexcept;
        treeview_item add_child(const std::wstring& caption) noexcept;

        std::wstring get_text() const;
        treeview_item& set_text(const wchar_t* text) noexcept;
        treeview_item& set_text(const std::wstring& text) noexcept;

        treeview_item& set_selected() noexcept;

        int get_icon_index() const noexcept;
        treeview_item& set_icon_index(int ilIconIndex) noexcept;

        LPARAM get_lparam() const noexcept;
        treeview_item& set_lparam(LPARAM lParam);
    };
}