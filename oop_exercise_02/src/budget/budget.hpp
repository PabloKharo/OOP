#pragma once
#include <iostream>

class Budget
{
private:
    double a; //собственная часть средств бюджета в рублях
    double b; //заемная часть средств бюджета рублях
public:
    Budget(const double& a_ = 0, const double& b_ = 0):
        a(a_), b(b_){};

    Budget operator+ (Budget budg); 
    Budget operator- (Budget budg);
    Budget operator* (double d); 
    Budget operator/ (double d); 

    bool operator== (Budget budget);
    bool operator< (Budget budget);
    bool operator> (Budget budget);

    friend std::ostream& operator<< (std::ostream &out, const Budget &budget);
    friend std::istream& operator>> (std::istream &in, Budget &budget);

    bool Check();
    void Repay();
};

Budget operator"" _budget(const char* str, size_t size);
