#include "Poly.h"
#include "Rational.h"
#include "DataBase.h"
extern DataBase __globalDB__;
Poly::Poly(Rational arr[], size_t arrSize){

	unsigned int deg = 0, numOfElements = 0;

	_DBIndex = __globalDB__.getNewIndex();

	for (int i = arrSize - 1; i >= 0; i--)
	{
		
		if (arr[i].getNumerator() == 0)
			continue;

		deg = arrSize - i - 1;
		__globalDB__.inputNewNode(_DBIndex, arr[i], deg);
		numOfElements++;

		//std::cout << arr[i] << std::endl;
		//std::cout << "Num Of Elements: " << numOfElements << std::endl;
		//std::cout << "i: " << i << std::endl;

	}

	if (!numOfElements)
		__globalDB__.inputNewNode(_DBIndex, Rational(), 0);
}

Poly::~Poly(){

}
std::ostream &operator<<(std::ostream &os, Poly pol){
	
	os << "My Index is: " << pol.getDbIndex() << " \n";
	__globalDB__.requestPrintInstance(pol.getDbIndex());

	bool success = false;
	
	while (true){
	
		polyElement current = __globalDB__.getNextPrintInstance(success);
		
		os << current._value << "X^" << current._deg;

		if (success)
			os << " + ";
		else
			break;
	}
	os << "\n";

	return os;
}