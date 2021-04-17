#pragma once

#include <iostream>
#include <fstream>

struct Point
{
    double X;
    double Y;

    Point() {}
    Point(double X_, double Y_) :
        X(X_), Y(Y_) {}

    Point operator+(const Point p)
    {
        this->X += p.X;
        this->Y += p.Y;
        return *this;
    }

    Point operator-(const Point p)
    {
        this->X -= p.X;
        this->Y -= p.Y;
        return *this;
    }
    Point operator/(const double d)
    {
        this->X /= d;
        this->Y /= d;
        return *this;
    }
    bool operator==(const Point p)
    {
        return this->X == p.X && this->Y == p.Y;
    }

};

std::ostream& operator<< (std::ostream& out, const Point point)
{
    // out << '(' << point.X << "," << point.Y << ')';
    out << point.X << ' ' << point.Y;
    return out;
}

std::istream& operator>> (std::istream& in, Point& point)
{
    in >> point.X;
    in >> point.Y;

    return in;
}

std::ofstream& operator<< (std::ofstream& out, const Point point)
{
    // out << '(' << point.X << "," << point.Y << ')';
    out << point.X << ' ' << point.Y;
    return out;
}

std::ifstream& operator>> (std::ifstream& in, Point& point)
{
    in >> point.X;
    in >> point.Y;

    return in;
}
