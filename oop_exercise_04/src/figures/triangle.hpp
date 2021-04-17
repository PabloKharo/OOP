#pragma once

#include <vector>
#include <iostream>
#include <cmath>

#include "sup.hpp"

template <typename T>
class Triangle
{
public:
    template < typename = typename std::enable_if<std::is_convertible<T,int>::value, T>::type>
    Triangle(){}
    std::pair<T,T> p1, p2, p3;
    double area;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Triangle<T>& tr)
{
    out << tr.p1 << ' ' << tr.p2 << ' ' << tr.p3;
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Triangle<T>& tr)
{
    std::pair<double, double> p1, p2, p3;
    in >> p1 >> p2 >> p3;

    std::vector<double> sides = { Dist(p1, p2), Dist(p2, p3), Dist(p1, p3) };

    bool CheckSides = true;
    if (sides[0] == 0)
        CheckSides = false;
    if (abs(sides[0] - sides[1]) > 0.001 || abs(sides[0] - sides[2]) > 0.001)
        CheckSides = false;

    if (!CheckSides)
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    double per = (sides[0] + sides[1] + sides[2])/2;
    tr.area = sqrt(per * (per - sides[0]) * (per - sides[1]) * (per - sides[2]));

    tr.p1 = p1;
    tr.p2 = p2;
    tr.p3 = p3;

    return in;
}

