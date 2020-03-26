/*** Bartlomiej Stepek ***/

#include "Z2.h"
#include "Polynomial.h"

Polynomial::Polynomial() {
    degree = 0, array_of_coefficients = new Z2[1];
    array_of_coefficients[0] = 0;
}

Polynomial::Polynomial(unsigned int _degree, Z2* array)
:   degree(_degree) {
    while(array[degree].number == 0 && degree>0)
        degree--;

    this->array_of_coefficients = new Z2[degree + 1];
    for(unsigned int i = 0; i <= degree; i++)
        array_of_coefficients[i] = array[i];
}


Polynomial:: Polynomial(const Polynomial& a) {
    this->degree = a.degree;
    this->array_of_coefficients = new Z2[this->degree + 1];
    for(unsigned int i =0; i <= this->degree; i++)
        this->array_of_coefficients[i] = a.array_of_coefficients[i];

}

const Z2& Polynomial:: operator[](unsigned int i) const{
    if(i > this->degree) {
        std::cout << "Invalid polynomial index\n";
        return this->array_of_coefficients[0];
    }
    else
        return this->array_of_coefficients[i];
}

Polynomial& Polynomial:: operator += (const Polynomial& b) {
    if(b.degree > this->degree) {
        Z2* coefficients = new Z2[b.degree + 1];
        for(unsigned int i = 0; i <= b.degree; i++) {
            if(i <= this->degree)
                coefficients[i] = b.array_of_coefficients[i] + this->array_of_coefficients[i];
            else
                coefficients[i] = b.array_of_coefficients[i];
        }
        this->degree = b.degree;
        array_of_coefficients = new Z2[degree + 1];
        for(unsigned int i =0; i<= b.degree; i++)
            this->array_of_coefficients[i] = coefficients[i];
        delete[] coefficients;
    }
    else {
        for(unsigned int i = 0; i <= b.degree; i++)
            array_of_coefficients[i] += b.array_of_coefficients[i];
    }
    while(this->array_of_coefficients[this->degree].number == 0 && this->degree > 0)
        this->degree--;

    return *this;
}

Polynomial& Polynomial:: operator *= (const Polynomial& b){
    unsigned int new_degree = this->degree + b.degree;
    Z2* coefficients = new Z2[new_degree + 1];
    for(unsigned int i = 0; i <= this->degree; i++)
        for(unsigned int j = 0; j <= b.degree; j++)
            coefficients[i+j] = coefficients[i+j] + (this->array_of_coefficients[i] * b.array_of_coefficients[j]);

    while(coefficients[new_degree].number == 0 && new_degree > 0)
        new_degree--;

    this->array_of_coefficients = new Z2[new_degree + 1];
    for(unsigned int i = 0; i <= new_degree; i++)
        this->array_of_coefficients[i] = coefficients[i];

    this->degree = new_degree;
    delete[]coefficients;
    return *this;
}

unsigned int Polynomial:: degre() const {
    return this->degree;
}

std::string Polynomial:: toString(std::string numberVar){
    std::string result;
    std::ostringstream ss;
    int tmp = -1;
    if(degree == 0 && array_of_coefficients[0] == 0)
        result = "0";
    if(array_of_coefficients[0].number != 0){
        result = "1";
        tmp = 0;
    }
    for(unsigned int i = 1; i < degree; i++){
        if(array_of_coefficients[i].number != 0){
            if(tmp == 0) {
                ss << "+";
                tmp = 1;
            }
            ss << numberVar << "^" << i << "+";
        }
    }
    if(degree > 0){
        if(tmp == 0)
            ss << "+";
        ss << numberVar << "^" << degree;
    }
    result += ss.str();
    return result;
}

Polynomial operator + (const Polynomial& a, const Polynomial& b) {
    if(a.degree >= b.degree) {
        Z2* coefficients = new Z2 [a.degree + 1];
        for(unsigned int i = 0; i <= a.degree; i++) {
            if(i <= b.degree)
                coefficients[i] = b.array_of_coefficients[i] +  a.array_of_coefficients[i];
            else
                coefficients[i] = a.array_of_coefficients[i];
        }
        return Polynomial(a.degree, coefficients);
    }
    else {
        Z2* coefficients = new Z2 [b.degree + 1];
        for(unsigned int i = 0; i <= b.degree; i++) {
            if(i <= a.degree)
                coefficients[i] = b.array_of_coefficients[i] +  a.array_of_coefficients[i];
            else
                coefficients[i] = b.array_of_coefficients[i];
        }
        return Polynomial(b.degree, coefficients);
    }
}

Polynomial operator * (const Polynomial& a, const Polynomial& b) {
    unsigned int degree = a.degree + b.degree;
    Z2* coefficients = new Z2 [(a.degree + b.degree) + 1 ];
    for(unsigned int i = 0; i <= a.degree; i++)
        for(unsigned int j = 0; j <= b.degree; j++)
            coefficients[i+j] = coefficients[i+j] + (a.array_of_coefficients[i] * b.array_of_coefficients[j]);

    Polynomial c(degree, coefficients);
    delete[] coefficients;
    return c;
}

void mod (const Polynomial u, const Polynomial v, Polynomial& q, Polynomial& r) {
    if(v.degree == 0 && v.array_of_coefficients[0].number == 1) {
        q = u;
        r.degree = 0;
        r.array_of_coefficients[0].number = 0;
        return;
    }
    else if(v.degree == 0 && v.array_of_coefficients[0].number == 0) {
        std::cout << "Division by zero\n";
        return;
    }
    else if (u.degree < v.degree) {
        q.degree = 0;
        q.array_of_coefficients[0].number = 0;
        r = u;
        return;
    }

    else if (u.degree == v.degree && u.degree > 0) {
        q.degree = 0;
        q.array_of_coefficients[0].number = 1;
        Polynomial tmp = u;
        r.degree = 0;
        for(int i = tmp.degree; i >= 0; i--)
            if(r.degree == 0 && (tmp.array_of_coefficients[i] - v.array_of_coefficients[i]).number != 0){
                r.degree = i;
                break;
            }

        r.array_of_coefficients = new Z2[r.degree +1];
        for(int i = r.degree; i>=0; i--)
            r.array_of_coefficients[i] = tmp.array_of_coefficients[i] - v.array_of_coefficients[i];

        return;
    }

    else if (u.degree > v.degree && v.degree > 0) {
        int shift;
        Polynomial pol = u;
        Z2* temp = new Z2[u.degree + 1];
        q.array_of_coefficients = new Z2[(u.degree - v.degree) + 1];
        q.degree = u.degree - v.degree;
        while (pol.degree >= v.degree) {
            shift = pol.degree - v.degree;

            for(int i = v.degree; i>= 0; i--)
                temp[shift + i] = v.array_of_coefficients[i];

            memset(temp, 0, shift);
            q.array_of_coefficients[pol.degree - v.degree] = pol.array_of_coefficients[pol.degree] / temp[shift + v.degree];

            for(int i = 0; i <= v.degree + shift; i++) {
                temp[i] = temp[i] * q.array_of_coefficients[pol.degree - v.degree];
                pol.array_of_coefficients[i] = pol.array_of_coefficients[i] - temp[i];
            }

            while(pol.array_of_coefficients[pol.degree].number == 0 && pol.degree > 0)
                pol.degree--;

        }
        r = pol;
        return;
    }
}
Polynomial operator / (const Polynomial& u, const Polynomial& v){
    if(v.degree == 0 && v.array_of_coefficients[0].number == 0){
        std::cout << "Division by zero\n";
        return u;
    }
    else {
        Polynomial q,r;
        mod(u,v,q,r);
        return q;
    }
}

Polynomial operator % (const Polynomial& u, const Polynomial& v){
    if(v.degree == 0 && v.array_of_coefficients[0].number == 0){
        std::cout << "Division by zero\n";
        return Polynomial();
    }
    else {
    	Polynomial q,r;
    	mod(u,v,q,r);
    	return r;
    }
}

std::ostream& operator << (std::ostream& out, const Polynomial& a){
    out << "{";
    for(unsigned int i =0; i< a.degree; i++)
        out << a.array_of_coefficients[i].number << ",";

    out << a.array_of_coefficients[a.degree].number << "}";

    return out;
}

std::istream& operator>> (std::istream &in, Polynomial& a) {
    char tmp[256];
    in.getline(tmp,256);
    Z2* coefficients = new Z2[256];
    int counter = 0, i = 0;
    while(tmp[i] != '{')
            i++;

    while(tmp[i] != '}') {
        if(tmp[i] == '1' || tmp[i] == '0')
            coefficients[counter++] = Z2(tmp[i]);
        i++;
    }
    a.degree = counter;
    a.array_of_coefficients = new Z2[counter + 1];
    for(int i = 0; i <= a.degree; i++)
        a.array_of_coefficients[i] = coefficients[i];
    while(a.array_of_coefficients[a.degree].number == 0 && a.degree != 0)
        a.degree--;
    delete[] coefficients;

    return in;
}
