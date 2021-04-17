// Харьков П. А., М8О-206Б
// Необходимо реализовать две шаблонных функции:
// 1.  Функция print печати фигур на экран std::cout  (печататься должны координаты вершин фигур). 
//          Функция должна принимать на вход std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).
// 2.  Функция square вычисления суммарной площади фигур. Функция должна принимать на вход std::tuple с фигурами, согласно варианту задания (минимум по одной каждого класса).
 
// Создать программу, которая позволяет:
// ·   Создает набор фигур согласно варианту задания (как минимум по одной фигуре каждого типа с координатами типа int и координатами типа double).
// ·   Сохраняет фигуры в std::tuple
// ·   Печатает на экран содержимое std::tuple с помощью шаблонной функции print.
// ·   Вычисляет суммарную площадь фигур в std::tuple и выводит значение на экран.
// Реализовать фигуры: 8-угольник, квадрат, треугольник.

#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

#include "figures/octagon.hpp"
#include "figures/square.hpp"
#include "figures/triangle.hpp"

using namespace std;

template <class T, int index = 0>
void print(T figures)
{
    if constexpr (index < tuple_size<T>::value)
    {
        cout << get<index>(figures) << endl;
        print<T, index + 1>(figures);
    }
}

template <class T, int index = 0>
double sum_area(T figures)
{
    if constexpr (index < tuple_size<T>::value)
        return get<index>(figures).area 
                + sum_area<T, index+1>(figures);
    return 0;
}


int main()
{
    Octagon<double> oct1;
    if(!(cin >> oct1))
    {
        cout << "Wrong first Octagon!" << endl;
        exit(-1);
    }

    Octagon<int> oct2;
    if(!(cin >> oct2))
    {
        cout << "Wrong second Octagon!" << endl;
        exit(-1);
    }

    Square<double> sq;
    if(!(cin >> sq))
    {
        cout << "Wrong square!" << endl;
        exit(-1);
    }

    Triangle<float> tr;
    if(!(cin >> tr))
    {
        cout << "Wrong triangle!" << endl;
        exit(-1);
    }


    tuple t = make_tuple(oct1, oct2, sq, tr);
    print(t);
    cout << sum_area(t) << endl;

    return 0;
}