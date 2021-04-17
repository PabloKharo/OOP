#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "money.h"

using namespace std;


bool IsNumber(char c)
{
    return c >= '0' && c <= '9';
}
pair<bool, Money> ParseString(string value)
{
    Money money;
    istringstream ss(value);

    int i = 0;
    char penny;
    if (ss.peek() == '-' || !(ss >> money.ruble)) 
        return {false, money};

    // считывание посимвольно копеек
    while (ss >> penny)
    {
        if (i == 0 && (penny == ',' || penny == '.')) {}
        else if (i == 1 && IsNumber(penny))
            money.penny += 10 * (penny - '0');
        else if (i == 2 && IsNumber(penny))
            money.penny += (penny - '0');
        else
            return {false, money};

        i++;
    }
    if(i == 1 || i == 2) // была считана только запятая или 1 знак
        return {false, money};
    return {true, money};
}

istream& operator>> (istream& in, Money& money)
{

    // считывание суммы денег и создание потока ввода из нее
    string str;
    in >> str;
    auto [ok, money_] = ParseString(str);
    if(ok == true)
        money = money_;
    else
        in.setstate(ios_base::failbit);
    
    return in;
}
ostream& operator<< (ostream& out, const Money& money)
{
    out << money.ruble;
    out << ',';
    out << setw(2) << setfill('0') << (int)money.penny;
    return out;
}
    
Money Money::operator+ (const Money& rhs)
{
    Money money;
    money.penny = (this->penny + rhs.penny) % 100;
    money.ruble = this->ruble + rhs.ruble + (this->penny + rhs.penny) / 100;
    return money;
}
Money Money::operator- (const Money& rhs)
{
    // если вычитается число большее, чем текущее, то будет возвращено 0 рублей 0 копеек
    Money money;
    if(*this > rhs)
    {
        if(this->penny >= rhs.penny) // нужно ли уменьшать на единицу рубль
        {
            money.penny = this->penny - rhs.penny;
            money.ruble = this->ruble - rhs.ruble;
        }
        else
        {
            money.penny = 100 - abs(this->penny - rhs.penny) % 100;
            money.ruble = this->ruble - rhs.ruble - 1;
        }     
    }   

    return money;
}
Money Money::operator* (const double& d)
{
    Money money;
    if(d >= 0) // результат должен быть неотрицательным
    {
        unsigned long long value = 100 * this->ruble + this->penny;
        money.ruble = (value * d) / 100;
        money.penny = (unsigned long long)(value * d) % 100;
    }
    return money;
}
Money Money::operator/ (const double& d) 
{
    Money money;
    if(d > 0) // нельзя делить деньги на 0 или на отрицательные числа
    {
        unsigned long long value = 100 * this->ruble + this->penny;
        money.ruble = (value / d) / 100;
        money.penny = (unsigned long long)(value / d) % 100;
    }

    return money;
}
double Money::operator/ (const Money& rhs)
{
    // double используется, так как деление денег на деньги безразмерная величина
    double money = -1; // для возврата при некорректном вводе
    if(rhs.ruble != 0 || rhs.penny != 0)
    {
        double left = this->ruble + this->penny/100.0;
        double right = rhs.ruble + rhs.penny/100.0;
        money = left / right; 
    } 
    return money;
}

// все можно было реализовать только с помощью <
bool Money::operator== (const Money& rhs)
{
    return this->ruble == rhs.ruble && this->penny == rhs.penny;
}
bool Money::operator> (const Money& rhs)
{
    if(this->ruble != rhs.ruble)
        return this->ruble > rhs.ruble;
    return this->penny > rhs.penny;
}
bool Money::operator>= (const Money& rhs)
{
    if (this->ruble != rhs.ruble)
        return this->ruble > rhs.ruble;
    return this->penny >= rhs.penny;
}
bool Money::operator< (const Money& rhs)
{
    if (this->ruble != rhs.ruble)
        return this->ruble < rhs.ruble;
    return this->penny < rhs.penny;
}
bool Money::operator<= (const Money& rhs)
{
    if (this->ruble != rhs.ruble)
        return this->ruble < rhs.ruble;
    return this->penny <= rhs.penny;
}