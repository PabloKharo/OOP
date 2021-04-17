#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include "point.hpp"

const double PI = 3.141592653589793;

class Figure
{
protected:
    std::vector<Point> points;
    std::vector<double> sides;
    Figure() {};
public:
    void PrintPoints();
    double Side(Point p1, Point p2);

    virtual Point Center() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;

};

void Figure::PrintPoints()
{
    for (int i = 0; i < points.size(); ++i)
        std::cout << points[i] << ' ';
}

double Figure::Side(Point p1, Point p2) 
{
    return sqrt(pow(p1.X - p2.X, 2) + pow(p1.Y - p2.Y, 2));
}
