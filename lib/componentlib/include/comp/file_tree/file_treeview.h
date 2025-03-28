#pragma once
namespace ctrl
{
    class file_treeview_item;
    class file_treeview_item_directory;
    class file_treeview_item_file;

    class file_treeview : public treeview
    {
        friend file_treeview_item;
        friend file_treeview_item_directory;
        friend file_treeview_item_file;

    private:
        int _folderIconId = -1;
        int _documentIconId = -1;

    public:
        file_treeview(base_control* parent);
        file_treeview(base_control* parent, const base_config& cfg);
        file_treeview(base_control* parent, int x, int y, int width, int height);

        file_treeview(file_treeview&&) noexcept;
        file_treeview(treeview&&) noexcept;

        file_treeview_item_directory add_directory(const wchar_t* name) noexcept;
        file_treeview_item_directory add_directory(directory root) noexcept;
        file_treeview_item_file add_file(const wchar_t* name) noexcept;
        file_treeview_item_file add_file(file f) noexcept;

        const int folder_icon_id() const noexcept;
        const int document_icon_id() const noexcept;

        //virtual LRESULT on_receive_message(UINT, WPARAM, LPARAM) override;

    protected:
        virtual void on_image_list_initialize(image_list* list) override;
    };
}