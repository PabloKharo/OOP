#pragma once

#include "figure.hpp"
#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>


class Octagon : public Figure
{
private:
    Point center;
    Point input_p;
public:
    Octagon(){}
    Octagon(std::istream& in){
        in >> *this;
    }
    Octagon(std::ifstream& in){
        in >> *this;
    }
    
    virtual Point Center() override;
    virtual double Perimeter() override;
    virtual double Area() override;
    virtual void PrintPoints(std::ostream&) override;
    virtual void PrintPoints(std::ofstream&) override;
    double Radius();

    friend std::istream& operator>>(std::istream& in, Octagon& sq);
    friend std::ifstream& operator>>(std::ifstream& in, Octagon& sq);
};

void Octagon::PrintPoints(std::ostream& out)
{
    out << "octagon ";
    for (size_t i = 0; i < points.size(); ++i)
        out << points[i] << ' ';
}

void Octagon::PrintPoints(std::ofstream& out)
{
    out << "octagon " << center << ' ' << points[0];
}

Point Octagon::Center()
{
    return center;
}

double Octagon::Radius()
{
    double radius = sqrt(pow(this->center.X - this->input_p.X, 2) 
                            + pow(this->center.Y - this->input_p.Y, 2));
    return radius;
}

double Octagon::Perimeter()
{
    double p = 2. * Radius() * sin(PI / 8);
    return p;
}

double Octagon::Area()
{
    double s = pow(Radius(), 2) * 8 * tan(PI / 8);
    return s;
}

std::istream& operator>>(std::istream& in, Octagon& tr)
{
    in >> tr.center;
    in >> tr.input_p;

    double angle = atan2(tr.input_p.X - tr.center.X, tr.input_p.Y - tr.center.Y) +  PI / 2;

    for (int i = 0; i < 8; ++i)
    {
        Point p;

        p.X = - tr.Radius() * cos(angle) + tr.center.X;
        p.Y = tr.Radius() * sin(PI - angle) + tr.center.Y;
        tr.points.push_back(p);
        angle += 2 * PI / 8;
    }

    return in;
}

std::ifstream& operator>>(std::ifstream& in, Octagon& tr)
{
    in >> tr.center;
    in >> tr.input_p;


    double angle = atan2(tr.input_p.X - tr.center.X, tr.input_p.Y - tr.center.Y) +  PI / 2;

    for (int i = 0; i < 8; ++i)
    {
        Point p;

        p.X = - tr.Radius() * cos(angle) + tr.center.X;
        p.Y = tr.Radius() * sin(PI - angle) + tr.center.Y;
        tr.points.push_back(p);
        angle += 2 * PI / 8;
    }

    return in;
}