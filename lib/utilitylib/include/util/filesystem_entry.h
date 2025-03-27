#pragma once

using namespace std::filesystem;

namespace util
{
    enum filesystem_type
    {
        Directory,
        File
    };

    class filesystem_entry
    {
    protected:
        path                fullName;
        filesystem_type     type;

    public:
        filesystem_entry(path name, filesystem_type fstype) :
            fullName(name),
            type(fstype)
        {}

        std::wstring name()
        {
            return fullName.wstring();
        }

        std::wstring dir()
        {
            return fullName.parent_path().wstring();
        }

        bool is_directory() const
        {
            return std::filesystem::is_directory(fullName);
        }

        const filesystem_type& fs_type() const
        {
            return type;
        }
    };
}