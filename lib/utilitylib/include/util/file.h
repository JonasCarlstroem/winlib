#pragma once

namespace util
{
    class file final : public filesystem_entry
    {
    public:
        file(std::wstring path) :
            filesystem_entry(path, filesystem_type::File)
        {}

        file(path p) :
            filesystem_entry(p, filesystem_type::File)
        {}

        file(const file& f) = default;
        file(file&& f) = default;
    };
}