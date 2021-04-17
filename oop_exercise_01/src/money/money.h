#pragma once
#include <iostream>
#include <string>
#include <cassert>

class Money
{
private:
    unsigned long long ruble;
    unsigned char penny;
    friend std::pair<bool, Money> ParseString(std::string value);
public:
    Money(): 
        ruble(0), penny(0){}
    Money(unsigned long long ruble_):
        ruble(ruble_), penny(0){}
    Money(unsigned long long ruble_, unsigned char penny_):
        ruble(ruble_), penny(penny_)
        { assert(penny < 100); }

    friend std::istream& operator>> (std::istream& in, Money& money);
    friend std::ostream& operator<< (std::ostream& out, const Money& money);

    Money operator+ (const Money& rhs);
    Money operator- (const Money& rhs);
    Money operator* (const double& d);
    Money operator/ (const double& d);
    double operator/ (const Money& rhs);

    bool operator== (const Money& rhs);
    bool operator> (const Money& rhs);
    bool operator>= (const Money& rhs);
    bool operator< (const Money& rhs);
    bool operator<= (const Money& rhs);

};

