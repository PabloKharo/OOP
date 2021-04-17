#pragma once
#include <iostream>

template <typename T>
std::istream& operator>>(std::istream& in, std::pair<T,T>& p)
{
    char comma, br1, br2;
    in >> br1;
    while(br1 != '(')
        in >> br1;
    in >> p.first >> comma >> p.second >> br2;
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::pair<T,T>& p)
{
    out << '(' << p.first << ", " << p.second << ')';
    return out;
}
