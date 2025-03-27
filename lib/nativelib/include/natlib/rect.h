#pragma once

namespace nat
{
    struct rect : RECT
    {
        rect()
        {

        }

        rect(LONG left, LONG top, LONG right, LONG bottom)
        {
            this->left = left;
            this->top = top;
            this->right = right;
            this->bottom = bottom;
        }

        BOOL is_empty() const { return IsRectEmpty(this); }
        BOOL set_empty() { return SetRectEmpty(this); }
        BOOL set(LONG left, LONG top, LONG right, LONG bottom)
        {
            return SetRect(this, left, top, right, bottom);
        }

        BOOL point_in_rect(LONG x, LONG y)
        {
            POINT pt = { x, y };
            return PtInRect(this, pt);
        }

        LONG x() const { return left; }
        LONG y() const { return top; }
        LONG width() const { return right - left; }
        LONG height() const { return bottom - top; }

        rect& operator=(RECT& rc)
        {
            this->left = rc.left;
            this->top = rc.top;
            this->right = rc.right;
            this->bottom = rc.bottom;
        }
    };
}