#include "pch.h"

window::window() : base_window() {
    create();
}

LPCTSTR window::class_name() const
{
    return TEXT("MainWindow");
}

LPCTSTR window::window_name() const
{
    return TEXT("Main Window");
}