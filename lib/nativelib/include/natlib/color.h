#pragma once

namespace nat
{
    class brush
    {
    private:
        HBRUSH  _brush;

    public:
        brush() : _brush((HBRUSH)(COLOR_WINDOW + 1)) {}
        brush(HBRUSH hbrush) : _brush(hbrush) {}
        brush(COLORREF ref) : _brush(CreateSolidBrush(ref)) {}

        operator HBRUSH& ()
        {
            return _brush;
        }
    };

    enum class colors : COLORREF
    {
        red = RGB(255, 0, 0),
        green = RGB(0, 255, 0),
        blue = RGB(0, 0, 255),
        black = RGB(0, 0, 0),
        white = RGB(255, 255, 255),
        darkgrey = RGB(51, 51, 51)
    };

    class base_color
    {
    private:
        COLORREF    _color_ref;
        brush       _brush;

    public:
        base_color() : _color_ref(), _brush() {}
        base_color(COLORREF ref) : _color_ref(ref), _brush(CreateSolidBrush(ref)) {}
        base_color(colors clr)  : _color_ref((COLORREF)clr), _brush(CreateSolidBrush(_color_ref)) {}

        base_color& operator=(COLORREF ref)
        {
            _color_ref = ref;
            _brush = CreateSolidBrush(ref);
            return *this;
        }

        base_color& operator=(colors clr)
        {
            _color_ref = (COLORREF)clr;
            _brush = CreateSolidBrush(_color_ref);
            return *this;
        }

        operator COLORREF& ()
        {
            return _color_ref;
        }

        brush& get_brush()
        {
            return _brush;
        }
    };

    template<colors c>
    class color : public base_color
    {
    public:
        color() : base_color((COLORREF)c) {}
    };
}