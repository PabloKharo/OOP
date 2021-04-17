#pragma once

#include "figure.hpp"
#include <iostream>
#include <cmath>


class Square : public Figure
{
private:
    bool CheckSides();
public:

    virtual Point Center() override;
    virtual double Perimeter() override;
    virtual double Area() override;

    friend std::istream& operator>>(std::istream& in, Square& sq);
};

Point Square::Center()
{
    Point center = (points[0] + points[2]) / 2;
    return center;
}

double Square::Perimeter()
{
    return sides[0] * 4;
}

double Square::Area()
{
    return sides[0] * sides[0];
}

bool Square::CheckSides()
{
    if (sides[0] == 0 || abs(sides[0] - sides[1]) > 0.001)
        return false;
    return true;
}

std::istream& operator>>(std::istream& in, Square& sq)
{
    Point p1, p2, p3, p4;
    std::cin >> p1 >> p3;
    p2 = { p1.X, p3.Y };
    p4 = { p1.Y, p2.X };

    sq.points = { p1, p2, p3, p4 };
    sq.sides = { sq.Side(p1, p2), sq.Side(p2, p3)};

    if (!sq.CheckSides())
        in.setstate(std::ios_base::failbit);

    return in;
}
