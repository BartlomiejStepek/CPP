/*** Bartlomiej Stepek ***/
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>

class Z2 {
public:
    short int number;
    Z2();
    Z2(short int a);
    operator short int() const;
    Z2& operator += (const Z2& b);
    Z2& operator *= (const Z2& b);
    Z2& operator /= (const Z2& b);
};

Z2 operator + (const Z2& a, const Z2& b);
Z2 operator * (const Z2& a, const Z2& b);
Z2 operator - (const Z2& a, const Z2& b);
Z2 operator / (const Z2& a, const Z2& b);
std::ostream& operator << (std::ostream& out, const Z2& a);
