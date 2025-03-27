#pragma once

namespace nat
{
    struct size : SIZE
    {
        size()
        {
            this->cx = 0;
            this->cy = 0;
        }

        size(LONG x, LONG y)
        {
            this->cx = x;
            this->cy = y;
        }

        size& operator=(SIZE& s)
        {
            this->cx = s.cx;
            this->cy = s.cy;

            return *this;
        }

        SIZE& operator=(size& sz)
        {
            this->cx = sz.cx;
            this->cy = sz.cy;

            return *this;
        }

        SIZE* operator&()
        {
            return (SIZE*)this;
        }
    };
}