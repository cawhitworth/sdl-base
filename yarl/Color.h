struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    explicit Color(unsigned int rgba)
    {
        r = (rgba >> 24) & 0xff;
        g = (rgba >> 16) & 0xff;
        b = (rgba >> 8) & 0xff;
        a = rgba & 0xff;
    }

    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) : r(r), g(g), b(b), a(a) {}
};