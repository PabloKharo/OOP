#include <iostream>
#include <sstream>
#include <cassert>
#include "budget.hpp"

using namespace std;

Budget Budget::operator+ (Budget budg)
{ 
    Budget budget(this->a + budg.a, this->b + budg.b);
    if(!budget.Check())
        return *this;
    return budget;
}
Budget Budget::operator- (Budget budg)
{
    Budget budget(this->a - budg.a, this->b - budg.b);
    if(!budget.Check())
        return *this;
    return budget;
}
Budget Budget::operator* (double d)
{
    Budget budget(this->a * d, this->b / d);
    if(!budget.Check())
        return *this;
    return budget;
}
Budget Budget::operator/ (double d)
{
    Budget budget(this->a / d, this->b / d);
    if(!budget.Check())
        return *this;
    return budget;
}
bool Budget::operator== (Budget budget)
{
    return this->a == budget.a && this->b == budget.b;
}
bool Budget::operator< (Budget budget)
{
    if(this->a != budget.a)
        return this->a < budget.a;
    return this->b > budget.b;
}
bool Budget::operator> (Budget budget)
{
    if(this->a != budget.a)
        return this->a > budget.a;
    return this->b < budget.b;
}

ostream& operator<< (ostream &out, const Budget &budget)
{
    cout.precision(2);
    out << fixed <<"Budget(" << budget.a << ", "<< budget.b << ")";
    return out;
}
istream& operator>> (istream &in, Budget &budget){
    Budget budg;
    if(!(in >> budg.a >> budg.b) || budg.a < 0 || budg.b < 0)
        in.setstate(ios_base::failbit);
    if(budg.a >= 0 && budg.b >= 0)
        budget = budg;
    return in;
}

bool Budget::Check()
{ 
    if(a < 0 || b < 0)
        return false;
    return true;
}
void Budget::Repay()
{
    if((*this).Check())
    {
        if(a > b)
        {
            a = a - b;
            b = 0;
        }
        else
        {
            b = b - a;
            a = 0;
        }
        
    }
}

Budget operator"" _budget(const char* str, size_t size)
{
    istringstream literal_stream(str);
    Budget budget;
    assert(literal_stream >> budget && "Error in literal definition");
    return budget;
}

