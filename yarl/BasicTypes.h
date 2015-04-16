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
    
    T Area() { return w*h; }

    T w;
    T h;
};

template<typename T>
inline bool operator==(Position_T<T> a, Position_T<T> b)
{
    return a.x == b.x && a.y == b.y;
}

template<typename T>
inline bool operator!=(Position_T<T> a, Position_T<T> b)
{
    return !(a == b);
}

template<typename T>
inline bool operator==(Size_T<T> a, Size_T<T> b)
{
    return a.w == b.w && a.h == b.h;
}

template<typename T>
inline bool operator!=(Size_T<T> a, Size_T<T> b)
{
    return !(a == b);
}


template<typename T>
inline T OffsetOf(Position_T<T> p, Size_T<T> s)
{
    return p.x + p.y * s.w;
}

template<typename T>
inline T Distance(Position_T<T> p1, Position_T<T> p2)
{
    auto sumSq = ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    return static_cast<T>(sqrt(sumSq));
}

using CoordType = int;

using Size = Size_T<CoordType>;
using Position = Position_T<CoordType>;
