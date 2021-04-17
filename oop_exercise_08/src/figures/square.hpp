#pragma once

#include "figure.hpp"
#include <iostream>
#include <fstream>
#include <cmath>


class Square : public Figure
{
private:
    bool CheckSides();
public:
    Square(){}
    Square(std::istream& in);
    Square(std::ifstream& in);

    virtual Point Center() override;
    virtual double Perimeter() override;
    virtual double Area() override;
    virtual void PrintPoints(std::ostream&) override;
    virtual void PrintPoints(std::ofstream&) override;
};

void Square::PrintPoints(std::ostream& out)
{
    out << "square ";
    for (size_t i = 0; i < points.size(); ++i)
        out << points[i] << ' ';
}

void Square::PrintPoints(std::ofstream& out)
{
    out << "square " << points[0] << ' ' << points[2];
}

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

Square::Square(std::istream& in)
{
    Point p1, p2, p3, p4;
    in >> p1 >> p3;
    p2 = { p1.X, p3.Y };
    p4 = { p3.Y, p1.X };

    points = { p1, p2, p3, p4 };
    sides = { Side(p1, p2), Side(p2, p3)};

}

Square::Square(std::ifstream& in)
{
    Point p1, p2, p3, p4;
    in >> p1 >> p3;
    p2 = { p1.X, p3.Y };
    p4 = { p3.Y, p1.X };

    points = { p1, p2, p3, p4 };
    sides = { Side(p1, p2), Side(p2, p3)};
}
