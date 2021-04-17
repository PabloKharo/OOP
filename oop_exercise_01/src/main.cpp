// Харьков Павел Александрович, М80-106Б-19

#include <iostream>
#include <string>
#include <limits>
#include "money/money.h"
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

template <typename T, typename V>
bool ScanVariables(T& t, V& v)
{
    if(cin >> t && cin >> v && (cin.peek() == '\n' || cin.peek() == EOF ||cin.peek() == '\r'))
        return true;
    ClearInput();
    PrintError();
    return false;
}

int main()
{
    Money money_1, money_2;
    double d;
    string command;

    cout << ">> ";
    while(cin >> command)
    {
        if(command == "add") // сложение
        {
            if (ScanVariables(money_1, money_2))
                cout << money_1 + money_2 << endl;
        }
        else if(command == "sub") // вычитание
        {
            if (ScanVariables(money_1, money_2))
                cout << money_1 - money_2 << endl;
        }
        else if(command == "div_money") // деление на money
        {
            if (ScanVariables(money_1, money_2))
                cout << money_1 / money_2 << endl;
        }
        else if(command == "div_double") // деление на double
        {
            if (ScanVariables(money_1, d))
                cout << money_1 / d << endl;
        }
        else if(command == "multi") // умножение
        {
            if (ScanVariables(money_1, d))
                cout << money_1 * d << endl;
        }
        else if(command == "compare") // сравнение
        {
            if (ScanVariables(money_1, money_2))
            {
                if (money_1 > money_2)
                    cout << "First is bigger" << endl;
                else if (money_1 < money_2)
                    cout << "Second is bigger" << endl;
                else
                    cout << "The amounts are equal" << endl;
            }
        }
        else if(command == "help")
        {
            string help = "COMMANDS:"
            "\n add \t\t - sum money with money"
            "\n sub \t\t - subtraction money from money"
            "\n \t\t    if (money1 - money2) < 0 it will return 0,0!"
            "\n div_money \t - division money by money"
            "\n \t\t    it will return double!"
            "\n div_double \t - division money by double"
            "\n multi \t\t - multiplication money by double"
            "\n compare \t - compare money with money"
            "\n help \t\t - print help"
            "\n quit \t\t - quit"
            "\nEXAMPLES:"
            "\n add 1,2 3,4"
            "\n multi 1,4 3.2"
            "\n compare 1,3 1,29";
            cout << help << endl;
            ClearInput();
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
