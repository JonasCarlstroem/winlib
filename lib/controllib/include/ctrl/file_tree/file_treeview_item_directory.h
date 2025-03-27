#pragma once

namespace ctrl
{
    class file_treeview_item_directory : public file_treeview_item
    {
    public:
        file_treeview_item_directory(HTREEITEM hti, file_treeview* owner, directory dir) :
            file_treeview_item(hti, owner, filesystem_type::Directory, dir)
        {}

        file_treeview_item_directory(file_treeview_item&& other) :
            file_treeview_item(std::move(other))
        {
            _filesystem_type = filesystem_type::Directory;
        }

        file_treeview_item_directory(file_treeview_item&& other, directory dir) :
            file_treeview_item(std::move(other), dir)
        {}

        std::wstring get_name() const
        {
            return get_text();
        }

        file_treeview_item_directory add_directory(const wchar_t* name) noexcept
        {
            return this->add_child<file_treeview_item_directory>(filesystem_type::Directory, name);
        }

        file_treeview_item_directory add_directory(directory dir) noexcept
        {
            SHFILEINFO fi = { 0 };

            SHGetFileInfo(dir.name().c_str(),
                          NULL,
                          &fi,
                          sizeof(SHFILEINFO),
                          SHGFI_ICON);

            int iconID = m_treeview->add_icon(fi.hIcon);

            return this->add_child_with_icon<file_treeview, file_treeview_item_directory>(
                dir.name(),
                iconID,
                dir
            );
        }

        file_treeview_item_file add_file(const wchar_t* name) noexcept
        {
            return this->add_child<file_treeview_item_file>(filesystem_type::File, name);
        }

        file_treeview_item_file add_file(file f) noexcept
        {
            SHFILEINFO fi = { 0 };

            SHGetFileInfo(f.name().c_str(),
                          NULL,
                          &fi,
                          sizeof(SHFILEINFO),
                          SHGFI_ICON);

            int iconID = m_treeview->add_icon(fi.hIcon);

            return this->add_child_with_icon<file_treeview, file_treeview_item_file>(
                f.name(),
                iconID,
                f
            );
        }

        operator file_treeview_item_directory* ()
        {
            return this;
        }
    };
}