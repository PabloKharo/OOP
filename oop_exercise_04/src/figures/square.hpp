#pragma once

#include <vector>
#include <iostream>
#include <cmath>

#include "sup.hpp"

template <typename T>
class Square
{
public:
    template < typename = typename std::enable_if<std::is_convertible<T,int>::value, T>::type>
    Square(){}
    std::pair<T,T> p1, p2, p3, p4;
    double area;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Square<T>& sq)
{
    out << sq.p1 << ' ' << sq.p2 << ' ' << sq.p3 << ' ' << sq.p4;
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Square<T>& sq)
{
    std::pair<T,T> p1, p2, p3, p4;
    in >> p1 >> p3;
    p2 = { p1.first, p3.second };
    p4 = { p1.second, p2.first };

    double side1 = Dist(p1, p2);
    double side2 = Dist(p2, p3); 

    bool CheckSides = true;
    if (side1 == 0 || abs(side1 - side2) > 0.001)
        CheckSides = false;

    if (!CheckSides)
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    sq.area = side1 * side1;

    sq.p1 = p1; sq.p2 = p2;
    sq.p3 = p3; sq.p4 = p4;

    return in;
}
