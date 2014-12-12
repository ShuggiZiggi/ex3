#pragma once
#include <iostream>
#include <cstddef>
#include <iterator>
#include "Rational.h"

#include "Poly.h"
//using namespace std;


int main()
{


	Rational coeffs1[] = { 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, { 17, 2 } };

	Rational coeffs2[] = { 14, 3, 5, 2, 0, 4, 4, 0, 5, 0, 6, 0, 7, 0, { 17, 2 } };

	//Poly p1(coeffs1,(size_t)15);

	Poly p2(coeffs2, (size_t)15);

	//std::cout << p1 + p2 << std::endl << std::endl << std::endl;
	//std::cout << "PRINTING P2\n\n";
	std::cout << p2;
	system("pause");
	return 0;
}