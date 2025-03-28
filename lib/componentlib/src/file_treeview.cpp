#include "pch.h"

namespace comp {
    file_treeview::file_treeview(base_control* parent) :
        treeview(parent) {}

    file_treeview::file_treeview(base_control* parent, const base_config& cfg) :
        treeview(parent, cfg) {}

    file_treeview::file_treeview(base_control* parent, int x, int y, int width, int height) :
        treeview(parent, x, y, width, height) {}

    file_treeview::file_treeview(file_treeview&& other) noexcept :
        treeview(std::move(other)) {}

    file_treeview::file_treeview(treeview&& tv) noexcept :
        treeview(std::move(tv)) {
        file_treeview&& ftv = reinterpret_cast<file_treeview&&>(tv);
        _folderIconId = std::exchange(ftv._folderIconId, 0);
        _documentIconId = std::exchange(ftv._documentIconId, 0);
    }

    file_treeview_item_directory file_treeview::add_directory(const wchar_t* name) noexcept {
        file_treeview_item tvitem = { (file_treeview_item)this->add_root_item_with_icon(name, _documentIconId), directory(path(name)) };
        return tvitem;
    }

    file_treeview_item_directory file_treeview::add_directory(directory root) noexcept {
        SHFILEINFO fi = { 0 };

        SHGetFileInfo(root.name().c_str(),
                      NULL,
                      &fi,
                      sizeof(SHFILEINFO),
                      SHGFI_ICON);

        int iconID = add_icon(fi.hIcon);

        return this->add_root_item_with_icon<
            file_treeview, file_treeview_item_directory
        >(root.name(), iconID, root);
    }

    file_treeview_item_file file_treeview::add_file(const wchar_t* name) noexcept {
        file_treeview_item tvitem = { (file_treeview_item)this->add_root_item_with_icon(name, _documentIconId), file(path(name)) };
        return tvitem;
    }

    file_treeview_item_file file_treeview::add_file(file f) noexcept {
        HMODULE mod = GetModuleHandle(f.name().c_str());

        return this->add_root_item_with_icon<
            file_treeview, file_treeview_item_file
        >(f.name(), _documentIconId, f);
    }

    const int file_treeview::folder_icon_id() const noexcept {
        return _folderIconId;
    }

    const int file_treeview::document_icon_id() const noexcept {
        return _documentIconId;
    }

    void file_treeview::on_image_list_initialize(image_list* list) {
        icon ic = icon::load(SIID_FOLDER);
        _folderIconId = list->add_icon(ic);

        ic = icon::load(SIID_DOCASSOC);
        _documentIconId = list->add_icon(ic);

        if (list->get_image_count() == 0) {
            throw std::exception("Error loading images...");
        }
    }
}