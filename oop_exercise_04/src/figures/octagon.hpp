#pragma once

#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

#include "sup.hpp"

const double PI = 3.141592653589793;

template <typename T>
class Octagon
{
public:
    template <typename = typename std::enable_if<std::is_convertible<T,int>::value, T>::type>
    Octagon() {}
    std::vector<std::pair<T,T>> points;
    double area;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Octagon<T>& oc)
{
    for(int i = 0; i < 8; ++i)
    {
        out << oc.points[i] << ' ';
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Octagon<T>& oc)
{
    std::pair<double,double> center;
    std::pair<double,double> input_p;

    in >> center >> input_p;
    if (center == input_p)
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }

    double Radius = Dist(center, input_p);
    oc.area = pow(Radius, 2) * 8 * tan(PI / 8);

    double angle = atan2(input_p.first - center.first, input_p.second - center.second) +  PI / 2;

    for (int i = 0; i < 8; ++i)
    {
        std::pair<T,T> p;

        p.first = - Radius * cos(angle) + center.first;
        p.second = Radius * sin(PI - angle) + center.second;
        oc.points.push_back(p);
        angle += 2 * PI / 8;
    }

    return in;
}