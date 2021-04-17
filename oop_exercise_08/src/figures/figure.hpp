#pragma once

#include <vector>
#include <iostream>
#include <fstream>
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
    virtual void PrintPoints(std::ostream&) = 0;
    virtual void PrintPoints(std::ofstream&) = 0;
    double Side(Point p1, Point p2);

    virtual Point Center() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;

};

double Figure::Side(Point p1, Point p2) 
{
    return sqrt(pow(p1.X - p2.X, 2) + pow(p1.Y - p2.Y, 2));
}
