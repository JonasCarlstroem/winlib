#pragma once

namespace
{
    void throw_error(const wchar_t* function)
    {
        LPVOID lpMsgBuf;
        LPVOID lpDisplayBuf;
        DWORD dw = GetLastError();

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpMsgBuf,
            0, NULL);

        lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
                                          (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)function) + 40) * sizeof(TCHAR));

        StringCchPrintf((LPTSTR)lpDisplayBuf,
                        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
                        TEXT("%s failed with error %d: %s"),
                        function, dw, lpMsgBuf);

        MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

        LocalFree(lpMsgBuf);
        LocalFree(lpDisplayBuf);
        ExitProcess(0);
    }

#pragma warning(push)
#pragma warning(disable: 4312 4244)

    template<class T>
    T _GetWindowLongPtr(HWND hwnd, int nIndex)
    {
        return (T)GetWindowLongPtr(hwnd, nIndex);
    }
    
    template<class T>
    LONG_PTR _SetWindowLongPtr(HWND hwnd, int nIndex, T p)
    {
        return SetWindowLongPtr(hwnd, nIndex, (LONG_PTR)p);
    }

#pragma warning(pop)

} //namespace

