#include "Poly.h"
#include "Rational.h"
#include "DataBase.h"
extern DataBase __globalDB__;
Poly::Poly(Rational arr[], size_t arrSize){

	unsigned int deg = 0;
	
	for (int i = arrSize - 1; i >= 0; i--)
	{
		
		if (arr[i].getNumerator() == 0)
			continue;

		deg = arrSize - i - 1;
		__globalDB__.inputNewNode(_DBIndex, arr[i], deg);
		items++;
	}

	if (!items)
		__globalDB__.inputNewNode(_DBIndex, Rational(), 0);
}

Poly::~Poly(){

}

//==================OPERATORS BLAT=====================//
std::ostream &operator<<(std::ostream &os, Poly pol){
	
	//std::cout << "Operator << !!!!!\n\n";
	__globalDB__.requestPrintInstance(pol.getDbIndex());

	bool success = false;
	
	while (true){
		std::cout << "LOOP START!\n";
		polyElement current = __globalDB__.getNextPrintInstance(success);
		std::cout << current.getDegree() << "--------------------------------\n";
		std::cout << current.getNext() << "--------------------------------\n";
		Rational Temp = current.getRational();
		os << Temp << "X^" /* <<current.getDegree()*/;
		std::cout << "LOOP END!\n";
		if (success)
		{
			std::cout << "SUCCESS\n";
			system("pause");
			os << " + ";
		}
		
		else
			break;
	}
	os << "\n";

	return os;
}

Poly::Poly()
{
//	_DBIndex = __globalDB__.getNewIndex();

	__globalDB__.inputNewNode(_DBIndex, Rational(), 0);
}

Poly::Poly(const Rational & rational){
//	_DBIndex = __globalDB__.getNewIndex();
	__globalDB__.inputNewNode(_DBIndex, rational, 0);
}

Poly::Poly(const int deg, const Rational& rational)
{
//	_DBIndex = __globalDB__.getNewIndex();

	__globalDB__.inputNewNode(_DBIndex, rational, deg);

}

//Poly::Poly(const Poly &original)
//{
//	_DBIndex = __globalDB__.getNewIndex();
//	__globalDB__.cloneListFromIndexToIndex(original.getDbIndex(), _DBIndex);
//}

Poly operator+(const Poly &L, const Poly &R){
	size_t arraySize = (L.deg() > R.deg()) ? L.deg()+1 : R.deg()+1;
	Rational *rationalPolyArr = new Rational[arraySize];

	for (int i = 0; i < arraySize; i++)
		rationalPolyArr[i] = 0;
	
	
	int rSize = R.getNumOfElements();
	int lSize = L.getNumOfElements();

	std::cout << "R Size is: " << rSize << " L size is: " << lSize << std::endl;
	return Poly(L);
	for (int index = 0; index < rSize; index++)
		rationalPolyArr[__globalDB__.getElementByIndexes(R.getDbIndex(), index).getDegree()] += __globalDB__.getElementByIndexes(R.getDbIndex(), index).getRational();

	for (int index = 0; index < lSize; index++)
		rationalPolyArr[__globalDB__.getElementByIndexes(L.getDbIndex(), index).getDegree()] += __globalDB__.getElementByIndexes(L.getDbIndex(), index).getRational();
	
	 Poly temp =  Poly(rationalPolyArr, arraySize);

	 delete[] rationalPolyArr;

	 return temp;
}

int Poly::deg()const{
	return __globalDB__.getElementByIndexes(getDbIndex(), 0).getDegree();
}

int Poly::getNumOfElements()const{
	return items;
}