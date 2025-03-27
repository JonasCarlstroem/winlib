#pragma once

#ifndef _UNICODE
#define main() WINAPI WinMain(_In_ HINSTANCE hInstance,             \
                              _In_opt_ HINSTANCE hPrevInstance,     \
                              _In_ LPSTR lpCmdLine,                 \
                              _In_ int nCmdShow)                        
#else
#define main() WINAPI wWinMain(_In_ HINSTANCE hInstance,            \
                               _In_opt_ HINSTANCE hPrevInstance,    \
                               _In_ LPWSTR lpCmdLine,               \
                               _In_ int nCmdShow)
#endif