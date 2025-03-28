#pragma once
#define C L"C"
#define TREEVIEWCTRL C WC_TREEVIEW

namespace ctrl
{
    class treeview_item;

    class treeview : public control
    {
        friend treeview_item;
    public:
        treeview(base_control* parent);
        treeview(base_control* parent, int x, int y, int width, int height);
        treeview(base_control* parent, const base_config& cfg);

        treeview(treeview&&) noexcept;
        treeview& operator=(treeview&&) = default;

        operator HWND ()
        {
            return get_handle<HWND>();
        }

        template<typename Ttreeview, typename Ttreeview_item, typename... Targs>
        Ttreeview_item add_root_item_with_icon(const std::wstring& text, int iconId, Targs... args)
        {
            TVINSERTSTRUCTW tvi{};
            tvi.hParent = TVI_ROOT;
            tvi.hInsertAfter = TVI_LAST;
            tvi.itemex.mask = TVIF_TEXT | (iconId == -1 ? 0 : (TVIF_IMAGE | TVIF_SELECTEDIMAGE));
            tvi.itemex.pszText = const_cast<wchar_t*>(text.data());
            tvi.itemex.iImage = iconId;
            tvi.itemex.iSelectedImage = iconId;

            return Ttreeview_item(
                TreeView_InsertItem(*this, &tvi),
                (Ttreeview*)this,
                args...
            );
        }

        treeview_item add_root_item_with_icon(const wchar_t*, int = -1) noexcept;
        treeview_item add_root_item_with_icon(const std::wstring&, int = -1) noexcept;

        treeview_item add_root_item(const wchar_t*) noexcept;
        treeview_item add_root_item(const std::wstring&) noexcept;

        HRESULT create() override final;

        int add_image(HBITMAP);
        int add_icon(HICON);
        virtual void set_bk_color(base_color) override;
        virtual void set_text_color(base_color) override;

    private:
        static bool         m_bRegistered;
        int                 count = 0;
        image_list* m_imageList = nullptr;
        base_color          m_prevbkColor;
        base_color          m_prevtxtColor;

        virtual HRESULT register_control() override;
        BOOL initialize();

        std::wstring get_text();
        bool insert_item(const TVINSERTSTRUCTW& tvins, treeview_item* item);
        void set_item(const TVITEMW& item);

        void attach_imagelist();

        virtual LRESULT on_init_dialog(const init_dialog_event& ev) override;
        virtual void on_created(const created_event& ev) override { attach_imagelist(); }

    protected:
        virtual void on_image_list_initialize(image_list* list) { return; }

        virtual BOOL sub_class() const final { return FALSE; }
        virtual BOOL custom_class() const override { return TRUE; }
        //virtual BOOL custom_control() const override { return TRUE; }
        virtual LPCWSTR class_name() const override { return WC_TREEVIEW; }
        virtual LPCWSTR window_name() const override { return TEXT("TreeViewControl"); }
        virtual LONG window_style() const override { return WS_EX_CLIENTEDGE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS; }
    };
}