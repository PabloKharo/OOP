#pragma once 

#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include "figures/figure.hpp"
#include "figures/octagon.hpp"
#include "figures/square.hpp"
#include "figures/triangle.hpp"

struct Factory{
    std::shared_ptr<Figure> CreateFigure(std::istream& in)
    {
        std::string fig;
        in >> fig;
        if(fig == "octagon")
            return std::shared_ptr<Figure>(new Octagon(in));
        else if(fig == "square")
            return std::shared_ptr<Figure>(new Square(in));
        else if(fig == "triangle")
            return std::shared_ptr<Figure>(new Triangle(in));
        
        throw "Invalid figure";
        
    }

    std::shared_ptr<Figure> CreateFigure(std::ifstream& in)
    {
        std::string fig;
        in >> fig;
        if(fig == "octagon")
            return std::shared_ptr<Figure>(new Octagon(in));
        else if(fig == "square")
            return std::shared_ptr<Figure>(new Square(in));
        else if(fig == "triangle")
            return std::shared_ptr<Figure>(new Triangle(in));

        throw "Invalid figure";
    }
};

