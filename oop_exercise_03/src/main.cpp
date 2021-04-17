//  Харьков Павел, М80-206Б-19

//Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure.Фигуры являются фигурами вращения.Все классы должны поддерживать набор общих методов :
//Вычисление геометрического центра фигуры;
//Вывод в стандартный поток вывода std::cout координат вершин фигуры;
//Вычисление площади фигуры;
//
//Создать программу, которая позволяет :
//Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
//Сохранять созданные фигуры в динамический массив std::vector<Figure*>
//Вызывать для всего массива общие функции(1 - 3 см.выше).Т.е.распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
//Необходимо уметь вычислять общую площадь фигур в массиве.
//Удалять из массива фигуру по индексу;
//Фигуры: 8-угольник, треугольник, квадрат

#include <iostream>
#include <string>
#include <vector>

#include "figures/figure.hpp"
#include "figures/triangle.hpp"
#include "figures/square.hpp"
#include "figures/octagon.hpp"

using namespace std;

int main()
{
    string command;
    vector<Figure*> v;
    cout << ">> ";
    while (cin >> command)
    {

        if (command == "add")
        {
            string figure;
            cin >> figure;
            if (figure == "triangle")
            {
                Triangle* t = new Triangle;
                if (!(cin >> *t))
                    cout << "Wrong figure!" << endl;
                v.push_back(t);
            }
            else if (figure == "square")
            {
                Square* s = new Square;
                if (!(cin >> *s))
                    cout << "Wrong figure!" << endl;
                v.push_back(s);

            }
            else if (figure == "octagon")
            {
                Octagon* o = new Octagon;
                if (!(cin >> *o))
                    cout << "Wrong figure!" << endl;
                v.push_back(o);

            }
            else
            {
                cout << "Wrong input!" << endl;
            }
        }
        else if (command == "print")
        {
            int i;
            cin >> i;
            --i;
            if (i < 0 || i >= v.size())
                cout << "Wrong input!" << endl;
            else
            {
                cout << "Vertexes: ";
                v[i]->PrintPoints();
                cout << endl;
                cout << "Center: " << v[i]->Center() << endl;
                cout << "Area: " << v[i]->Area() << endl;
            }
        }  
        else
        {
            cout << "Wrong input!" << endl;
        }
        cin.clear();

        cout << ">> ";
    }

    for (int i = 0; i < v.size(); ++i)
    {
        delete v[i];
    }


    return 0;
}
