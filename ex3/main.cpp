
#include <iostream>
#include <cstddef>
#include <iterator>
#include "Rational.h"

#include "Poly.h"

//using namespace elranTheHomo;


int main()
{
	//Rational coeffs1[] = { 15, 0, 0, 5, 0, 0, 0, 3, 0, 0, 0, 0, 5, 0, { 17, 2 } };

//	Rational coeffs2[] = { 14, 3, 5, 2, 0, 4, 4, 0, 5, 0, 6, 0, 7, 0, { 17, 2 } };
  
    Rational coeffs1[] = {9,7,5,6,0,{3,1}};
    Rational coeffs2[] = {2,0,{0,1}};
    
    Poly c1(coeffs1,4);
    Poly c2(coeffs2,3);
    
    //std::cout << c2 / Rational(5);
    std::cout <<"("<<  c1 << ")%(" << c2  << ") = \n" << c1.gcd(c2)<< std::endl;
    
    system( "read -n 1 -s -p \"Press any key to continue...\"" );
    return 0;
}