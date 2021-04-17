// Харьков П.А., М80-206Б-19

//Создать шаблон динамической коллекцию, согласно варианту задания :
//Коллекция должна быть реализована с помощью умных указателей(std::shared_ptr, std::weak_ptr).Опционально использование std::unique_ptr.
//В качестве параметра шаблона коллекция должна принимать тип данных - фигуры.
//Реализовать forward_iterator по коллекции.
//Коллекция должны возвращать итераторы begin() и  end().
//Коллекция должна содержать метод вставки на позицию итератора insert(iterator).
//Коллекция должна содержать метод удаления из позиции итератора erase(iterator).
//При выполнении недопустимых операций(например выход за границы коллекции или удаление несуществующего элемента) необходимо генерировать исключения.
//Итератор должен быть совместим со стандартными алгоритмами(например, std::count_if)
//Коллекция должна содержать метод доступа к элементу по оператору[].
//Реализовать программу, которая:
//Позволяет вводить с клавиатуры фигуры(с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию.
//Позволяет удалять элемент из коллекции по номеру элемента.
//Выводит на экран введенные фигуры с помощью std::for_each; Выводит на экран количество объектов, у которых площадь меньше заданной(с помощью  std::count_if).


#include <iostream>
#include <algorithm> 
#include <string>

#include "darray.hpp"
#include "trapez.hpp"

using namespace std;

void ClearInput()
{
    // очистка потока до конца строки
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void PrintError()
{  
    cout << "Wrong input!" << endl;
}

template <class T>
bool ScanVariable(T& t)
{
    if(cin >> t && (cin.peek() == '\n' || cin.peek() == EOF || cin.peek() == '\r'))
        return true;
    ClearInput();
    PrintError();
    return false;
}

int main()
{
    int n;
    while (cin >> n && n < 0) {
        cout << "Wrong size! Enter size: " << endl;
    }
    DArray<Trapezoid<int>> arr(n);
    string command;
    //cout << ">> ";
    while(cin >> command)
    {
        if(command == "set")
        {   
            size_t index;
            cin >> index;
            --index;
            if(index >= 0 && index < arr.Size())
            {
                Trapezoid<int> t;
                if(ScanVariable(t))
                    arr[index] = t;
            }
            else
            {
                ClearInput();
                PrintError();
            }
            
        }
        else if(command == "clear")
        {
            size_t index;
            cin >> index;
            --index;
            if(index >= 0 && index < arr.Size())
                arr[index].Clear();
            else
            {
                ClearInput();
                PrintError();
            }
        }
        else if(command == "print")
        {
            for(const auto& c: arr)
                cout << c << ", area: " << c.area << endl;
            ClearInput();
        }
        else if(command == "count")
        {
            int x;
            cin >> x;
            int res = count_if(arr.begin(), arr.end(), [x](Trapezoid<int> t)
                    {
                        if(t.area < x && t.area != 0)
                            return 1;
                        return 0;
                    });
            cout << res << " areas less than " << x << "\n"; 
        }
        else if(command == "resize")
        {
            size_t x;
            cin >> x;
            if(x >= 0)
                arr.Resize(x);
            else
            {
                ClearInput();
                PrintError();
            }
        }
        else
        {
            ClearInput();
            PrintError();
        }

        //cout << ">> ";

    }


    return 0;
}
