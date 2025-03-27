#pragma once
#include "cassert"

namespace util
{
    class file;

    class directory final : public filesystem_entry
    {
    public:
        directory(std::wstring path) :
            filesystem_entry(path, filesystem_type::Directory)
        {}

        directory(path p) :
            filesystem_entry(p, filesystem_type::Directory)
        {}

        std::vector<path> get_file_paths(bool includeSubDirs = false) const
        {
            std::vector<path> result;

            if (includeSubDirs)
            {
                result = internal_get_paths<File, recursive_directory_iterator>();
            }
            else
            {
                result = internal_get_paths<File, directory_iterator>();
            }

            return result;
        }

        std::vector<file> get_files(bool includeSubDirs = false) const
        {
            std::vector<file> result;

            if (includeSubDirs)
            {
                result = internal_get_items<file, File, recursive_directory_iterator>();
            }
            else
            {
                result = internal_get_items<file, File, directory_iterator>();
            }

            return result;
        }

        std::vector<path> get_directory_paths(bool includeSubDirs = false) const
        {
            std::vector<path> result;

            if (includeSubDirs)
            {
                result = internal_get_paths<Directory, recursive_directory_iterator>();
            }
            else
            {
                result = internal_get_paths<Directory, directory_iterator>();
            }

            return result;
        }

        std::vector<directory> get_directories(bool includeSubDirs = false) const
        {
            std::vector<directory> result;

            if (includeSubDirs)
            {
                result = internal_get_items<directory, Directory, recursive_directory_iterator>();
            }
            else
            {
                result = internal_get_items<directory, Directory, directory_iterator>();
            }

            return result;
        }

    private:

        template<filesystem_type fstype, typename iterator>
        std::vector<path> internal_get_paths() const
        {
            std::vector<path> res;

            for (iterator i(fullName), end; i != end; ++i)
            {
                switch (fstype)
                {
                    case Directory:
                    {
                        if (::is_directory(i->path()))
                        {
                            res.push_back(i->path());
                        }
                        break;
                    }
                    case File:
                    {
                        if (!::is_directory(i->path()))
                        {
                            res.push_back(i->path());
                        }
                        break;
                    }
                }
            }

            return res;
        }

        template<typename Tfilesystem_type, filesystem_type type, typename iterator>
        std::vector<Tfilesystem_type> internal_get_items() const
        {
            static_assert(std::is_base_of<filesystem_entry, Tfilesystem_type>::value, "FSType must derive from type filesystem_entry");
            std::vector<Tfilesystem_type> res;

            for (iterator i(fullName), end; i != end; ++i)
            {
                switch (type)
                {
                    case Directory:
                    {
                        if (::is_directory(i->path()))
                        {
                            res.push_back(Tfilesystem_type(i->path()));
                        }
                        break;
                    }
                    case File:
                    {
                        if (!::is_directory(i->path()))
                        {
                            res.push_back(Tfilesystem_type(i->path()));
                        }
                        break;
                    }
                }
            }

            return res;
        }
    };
}