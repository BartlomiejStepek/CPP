/*** Bartlomiej Stepek ***/

#include "Z2.h"

Z2::Z2() : number(0) {};

Z2::Z2(short int a) {
    if((a % 2 == 1) || (a % 2 == -1))
        number = 1;
    else
        number = 0;
}

Z2:: operator short int() const {
    return number;
}

Z2& Z2:: operator += (const Z2& b) {
    if((this->number == 0 && b.number == 0) || (this->number == 1 && b.number == 1))
        this->number = 0;
    else
        this->number = 1;
    return *this;
}

Z2& Z2:: operator *= (const Z2& b) {
    if(this->number == 1 && b.number == 1)
        this->number = 1;
    else
        this->number = 0;
    return *this;
}

Z2& Z2:: operator /= (const Z2& b) {
    if((this->number == 0 && b.number == 0) || (this->number == 1 && b.number == 0))
            std::cout << "Divide by zero\n";
    return *this;
}

Z2 operator + (const Z2& a, const Z2& b) {
    if((a.number == 0 && b.number ==0) || (a.number == 1 && b.number == 1))
        return Z2(0);
    else
        return Z2(1);
}

Z2 operator * (const Z2& a, const Z2& b) {
    if(a.number == 1 && b.number == 1)
        return Z2(1);
    else
        return Z2(0);
}

Z2 operator / (const Z2& a, const Z2& b) {
    if((a.number == 0 && b.number == 0) || (a.number == 1 && b.number == 0)){
        std::cout << "Divide by zero\n";
        return a;
    }
    return Z2(a.number);
}

Z2 operator - (const Z2& a, const Z2& b) {
    if((a.number == 1 && b.number == 1) || (a.number == 0 && b.number == 0))
        return Z2(0);
    else
        return Z2(1);
}

std::ostream& operator << (std::ostream& out, const Z2& a) {
    out << a.number;
    return out;
}
