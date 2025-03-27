#pragma once

namespace ctrl
{
    class file_treeview_item_file : protected file_treeview_item
    {
    public:
        file_treeview_item_file(HTREEITEM hti, file_treeview* owner, file f) :
            file_treeview_item(hti, owner, filesystem_type::File, f)
        {};

        file_treeview_item_file(file_treeview_item&& other) :
            file_treeview_item(std::move(other))
        {
            _filesystem_type = filesystem_type::File;
        }

        std::wstring name() const
        {
            return get_text();
        }
    };
}