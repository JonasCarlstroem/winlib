#pragma once

namespace ctrl
{
    class window : public base_window
    {
    public:
        window();

        virtual LPCTSTR class_name() const override;
        virtual LPCTSTR window_name() const override;
    };
}