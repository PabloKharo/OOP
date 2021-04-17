#pragma once
#include <iostream>

template <typename T>
std::istream& operator>>(std::istream& in, std::pair<T,T>& p)
{
    in >> p.first >> p.second;
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::pair<T,T>& p)
{
    out << '(' << p.first << ", " << p.second << ')';
    return out;
}

template <typename T>
double Dist(std::pair<T,T>& p1, std::pair<T,T>& p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}