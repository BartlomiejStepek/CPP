/*** Bartlomiej Stepek ***/
#include "Z2.h"
#include "Polynomial.h"
#include "Z2.cpp"
#include "Polynomial.cpp"
#include <iostream>
#include <sstream>

int main(){
      Z2 x(3), y(2);

      std::cout << x << std::endl;
      std::cout << y << std::endl;
      std::cout << x+y << std::endl;
      std::cout << x*y << std::endl;

      std::istringstream in("numbers{0,1,1}");
      Polynomial w;
      in >> w;
      std::cout  << w << std::endl;
      std::cout << w.toString("x") << std::endl;

      const int N1 = 10;
      const int N2 = 3;
      Z2 d1[N1+1] = {Z2(0),Z2(4),Z2(5),Z2(2),Z2(6),Z2(1),Z2(0)};
      Z2 d2[N2+1] = {Z2(0),Z2(1),Z2(1),Z2(3)};
      d1[N1] = 1;
      Polynomial u(N1,d1), v(N2,d2);
      std::cout << u << std::endl;
      std::cout << v << std::endl;
      std::cout << u+v << std::endl;
      std::cout << u*v << std::endl;

      std::cout << (u*v).toString("m") << std::endl;
      std::cout << (u/v).toString("d") << std::endl;

      Polynomial q, r;
      mod(u,v,q,r);
      std::cout << q.toString("q") << std::endl;
      std::cout << r.toString("r") << std::endl;

      return 0;
}
