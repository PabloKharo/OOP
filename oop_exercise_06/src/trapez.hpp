#pragma once

#include <iostream>
#include <cmath>
#include "suppair.hpp"

template <class T>
class Trapezoid
{
public:
    std::pair<T,T> a,b,c,d;
    double area;
    void Clear();
    Trapezoid()
    {
        area = 0;
        a = { 0, 0 }; b = { 0, 0 };
        c = { 0, 0 }; d = { 0, 0 };
    }
};

template <class T>
void Trapezoid<T>::Clear()
{
    Trapezoid<T> tmp;
    (*this) = tmp;
}

template <class T>
bool CheckY(std::pair<T,T>& a, std::pair<T,T>& b, std::pair<T,T>& c, std::pair<T,T>& d)
{
    if(a.second == b.second)
    {
        if(c.second != d.second)
            return false;
        
        std::pair<T,T> tmp = b;
        b = d;
        d = tmp;
        
    }
    else if(a.second == c.second)
    {
        if(b.second != d.second)
            return false;
        
        std::pair<T,T> tmp = c;
        c = d;
        d = tmp;
    }
    else if(a.second == d.second)
    {
        if(b.second != c.second)
            return false;
    }
    else
        return false;

    return true;
}

template <class T>
bool CheckX(std::pair<T,T>& a, std::pair<T,T>& b, std::pair<T,T>& c, std::pair<T,T>& d)
{
    if(a.first == b.first)
    {
        if(c.first != d.first)
            return false;

        std::pair<T,T> tmp = b;
        b = d;
        d = tmp;
    }
    else if(a.first == c.first)
    {
        if(b.first != d.first)
            return false;

        std::pair<T,T> tmp = c;
        c = d;
        d = tmp;
    }
    else if(a.first == d.first)
    {
        if(b.first != c.first)
            return false;
    }
    else
        return false;

    return true;
}

template <class T>
std::istream& operator>>(std::istream& in, Trapezoid<T>& t)
{
    std::pair<T, T> a, b, c, d;
    in >> a >> b >> c >> d;
    if (a == b || a == c || a == d || b == c || b == d || c == d)
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    if(CheckY(a, b, c, d))
    {
        t.area = ((std::abs(d.first - a.first) + std::abs(c.first - b.first)) / 2.0 ) * std::abs(b.second - a.second);
        t.a = a; t.b = b; t.c = c; t.d = d;
    }
    else if(CheckX(a, b, c, d))
    {
        t.area = ((std::abs(a.second - d.second) + std::abs(b.second - c.second)) / 2.0 ) * std::abs(b.first - a.first);
        t.a = a; t.b = b; t.c = c; t.d = d;
    }
    else
        in.setstate(std::ios_base::failbit);
    
    return in;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Trapezoid<T>& t)
{
    out << t.a << ' ' << t.b << ' ' << t.c << ' ' << t.d;
    return out;
}
