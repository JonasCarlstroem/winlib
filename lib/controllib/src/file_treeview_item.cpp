#include "pch.h"

file_treeview_item::file_treeview_item(HTREEITEM hti, file_treeview* owner, filesystem_type type, filesystem_entry entry) :
    treeview_item(hti, owner),
    _file_treeview(owner),
    _filesystem_type(type),
    _filesystem_entry(entry)
{}

file_treeview_item::file_treeview_item(file_treeview_item&& other) noexcept :
    treeview_item(std::move(other)),
    _file_treeview(std::move((file_treeview*)other.m_treeview)),
    _filesystem_type(std::move(other._filesystem_type)),
    _filesystem_entry(std::move(other._filesystem_entry))
{}

file_treeview_item::file_treeview_item(file_treeview_item&& other, filesystem_entry entry) noexcept :
    treeview_item(std::move(other)),
    _file_treeview(std::move((file_treeview*)other.m_treeview)),
    _filesystem_type(entry.fs_type()),
    _filesystem_entry(entry)
{}

file_treeview_item::file_treeview_item(treeview_item&& item) noexcept :
    file_treeview_item((file_treeview_item&&)item)
{}