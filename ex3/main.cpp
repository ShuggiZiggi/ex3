#include <iostream>

#include "Rational.h"

//using namespace std;

int main()
{
	Rational a(1, 3), b(1,2), c, d;

	b +=(a + a + a + a + a);

	std::cout << b << " " << a <<" " << a * b <<" " << a * a;

	getchar();

	return 0;
}