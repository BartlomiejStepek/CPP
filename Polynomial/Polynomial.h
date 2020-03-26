/*** Bartlomiej Stepek ***/
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>

class Polynomial {
public:
    unsigned int degree;
    Z2* array_of_coefficients;
    Polynomial();
    Polynomial(unsigned int _degree, Z2* array);
    Polynomial(const Polynomial& a);
    const Z2& operator[](unsigned int i) const;
    Polynomial& operator += (const Polynomial& b);
    Polynomial& operator *= (const Polynomial& b);
    unsigned int degre() const;
    std::string toString(std::string xVar);
};

Polynomial operator + (const Polynomial& a, const Polynomial& b);
Polynomial operator * (const Polynomial& a, const Polynomial& b);
void mod (const Polynomial u, const Polynomial v, Polynomial& q, Polynomial& r);
Polynomial operator / (const Polynomial& u, const Polynomial& v);
Polynomial operator % (const Polynomial& u, const Polynomial& v);
std::ostream& operator << (std::ostream& out, const Polynomial& a);
std::istream& operator>>(std::istream &in, Polynomial& a);
