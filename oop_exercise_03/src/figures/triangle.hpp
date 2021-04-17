#pragma once

#include "figure.hpp"
#include <iostream>
#include <cmath>


class Triangle : public Figure
{
private:
    bool CheckSides();
public:

    virtual Point Center() override;
    virtual double Perimeter() override;
    virtual double Area() override;
    
    friend std::istream& operator>>(std::istream& in, Triangle& triangle);
};

Point Triangle::Center()
{
    Point center = (points[0] + points[1] + points[2]) / 3; 
    return center;
}

double Triangle::Perimeter()
{
    return sides[0] + sides[1] + sides[2];
}

double Triangle::Area()
{
    double p = Perimeter()/2;
    return sqrt(p * (p - sides[0]) * (p - sides[1]) * (p - sides[2]));
}

bool Triangle::CheckSides()
{
    if (sides[0] == 0)
        return false;
    if (abs(sides[0] - sides[1]) > 0.001 || abs(sides[0] - sides[2]) > 0.001)
        return false;
    return true;
}

std::istream& operator>>(std::istream& in, Triangle& tr)
{
    Point p1, p2, p3;
    std::cin >> p1 >> p2 >> p3;

    tr.points = { p1, p2, p3 };
    tr.sides = { tr.Side(p1, p2), tr.Side(p2, p3), tr.Side(p1, p3) };

    if (!tr.CheckSides())
        in.setstate(std::ios_base::failbit);

    return in;
}

