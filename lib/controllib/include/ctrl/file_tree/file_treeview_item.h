#pragma once

namespace ctrl
{
    class file_treeview;

    class file_treeview_item : public treeview_item
    {
        friend file_treeview;
    protected:
        file_treeview* _file_treeview;
        filesystem_type     _filesystem_type;
        filesystem_entry    _filesystem_entry;

        file_treeview_item(HTREEITEM hti, file_treeview* owner, filesystem_type type, filesystem_entry entry);
        file_treeview_item(file_treeview_item&& other) noexcept;
        file_treeview_item(file_treeview_item&& other, filesystem_entry entry) noexcept;
        file_treeview_item(treeview_item&&) noexcept;

        file_treeview_item& operator=(file_treeview_item&& other) noexcept
        {
            this->_file_treeview = std::move(other._file_treeview);
            this->_filesystem_type = std::move(other._filesystem_type);
            treeview_item::operator=(std::move(other));

            return *this;
        }

        file_treeview_item& operator=(treeview_item&& other)
        {
            return (file_treeview_item&)treeview_item::operator=(std::move(other));
        }

        operator file_treeview_item* ()
        {
            return this;
        }

        template<typename Ttreeview_item>
        Ttreeview_item add_child(filesystem_type type, const wchar_t* name)
        {
            static_assert(std::is_base_of<file_treeview_item, Ttreeview_item>::value, "Template type must derive from type file_treeview_item");
            int iconId = -1;
            switch (type)
            {
                case filesystem_type::Directory:
                {
                    iconId = this->_file_treeview->folder_icon_id();
                    break;
                }
                case filesystem_type::File:
                {
                    iconId = this->_file_treeview->document_icon_id();
                    break;
                }
            }

            return (Ttreeview_item)treeview_item::add_child_with_icon(name, iconId);
        }

        template<typename Ttreeview_item>
        Ttreeview_item add_child(filesystem_type type, filesystem_entry entry)
        {
            static_assert(std::is_base_of<file_treeview_item, Ttreeview_item>::value, "Template type must derive from type file_treeview_item");
            int iconId = -1;
            switch (type)
            {
                case filesystem_type::Directory:
                {
                    iconId = this->_file_treeview->folder_icon_id();
                    break;
                }
                case filesystem_type::File:
                {
                    iconId = this->_file_treeview->document_icon_id();
                }
            }

            Ttreeview_item it = (Ttreeview_item)treeview_item::add_child_with_icon(entry.name(), iconId);
            file_treeview_item tvitem = treeview_item::add_child_with_icon(entry.name(), iconId);
            Ttreeview_item ret = (Ttreeview_item&&)tvitem;
            return it;
        }
    };
}