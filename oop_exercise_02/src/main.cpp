//Харьков Павел Александрович, М80-106Б-19
/*
Создать класс Budget для работы с бюджетом. Класс состоит из двух вещественных чисел (a,b). 
Где a – собственная часть средств бюджета в рублях, b – заемная часть средств бюджета рублях. Оба числа должны округляться до второго знака после запятой. 
Реализовать арифметические операции сложения, вычитания, умножения и деления, а также операции сравнения в виде перегрузки операторов.
Необходимо реализовать пользовательский литерал для работы с константами типа Budget.
*/
#include <iostream>
#include <limits>
#include "budget/budget.hpp"

using namespace std;

void ClearInput()
{
    // очистка потока до конца строки
    cin.clear();
    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}
void PrintError()
{  
    cout << "Wrong input!" << endl;
}

template <typename T>
bool ScanVariable(T& t)
{
    if(cin >> t && (cin.peek() == '\n' || cin.peek() == EOF ||cin.peek() == '\r'))
        return true;
    ClearInput();
    PrintError();
    return false;
}

int main (){
    double d;
    Budget budget_2;
    Budget budget = "1.1 1"_budget;
    cout << "Текущее значение: " << budget << endl;
    cout << ">> ";

    string command;
    while(cin >> command)
    {
        if(command == "add") // сложение
        {
            if (ScanVariable(budget_2))
            {
                budget = budget + budget_2;
                cout << budget << endl;
            }
        }
        else if(command == "sub") // вычитание
        {
            if (ScanVariable(budget_2))
            {
                budget = budget - budget_2;
                cout << budget << endl;
            }
        }
        else if(command == "div") // деление на double
        {
            if (ScanVariable(d))
            {
                budget = budget / d;
                cout << budget << endl;
            }
        }
        else if(command == "multi") // умножение на double
        {
            if (ScanVariable(d))
            {
                budget = budget * d;
                cout << budget << endl;
            }
        }
        else if(command == "compare") // сравнение
        {
            if (ScanVariable(budget_2))
            {
                if (budget > budget_2)
                    cout << "Literal value is bigger" << endl;
                else if (budget < budget_2)
                    cout << "Entered value is bigger" << endl;
                else
                    cout << "The budgets are equal" << endl;
            }
        }
        else if(command == "repay")
        {
            budget.Repay();
            cout << budget << endl;
        }
        else if(command == "set")
        {
            if (ScanVariable(budget_2))
            {
                budget = budget_2;
                cout << budget << endl;
            }
        }
        else if(command == "quit") // выход
        {
            break;
        }
        else
        {
            ClearInput();
            PrintError();         
        }

        cout << ">> ";     
    }

    return 0;
}


