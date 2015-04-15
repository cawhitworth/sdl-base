#pragma once

template<typename T>
struct Position_T
{
    Position_T() {}
    Position_T(T x, T y) : x(x), y(y) {}

    T x;
    T y;
};

template<typename T>
struct Size_T
{
    Size_T() {}
    Size_T(T w, T h) : w(w), h(h) {}

    T w;
    T h;
};

using CoordType = unsigned int;

using Size = Size_T<CoordType>;
using Position = Position_T<CoordType>;
