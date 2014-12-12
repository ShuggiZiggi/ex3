#pragma once
#include <stdlib.h>
#include <iosfwd>
#include <ostream>
#include <iostream>
#include <cstddef>

#include "Rational.h"
#include "DataBase.h"
extern DataBase __globalDB__;
class Poly
{
public:
	Poly(Rational[], size_t);
	Poly(const int,const Rational&);
	Poly(const Poly &);
	Poly();
	Poly(const Rational &);
	int deg()const;
	int getNumOfElements()const;
	unsigned int getDbIndex() const{
		return _DBIndex;
	}
	~Poly();

private:
	int items = 0;
	const unsigned int _DBIndex = __globalDB__.getNewIndex();
};


std::ostream &operator<<(std::ostream &, Poly);

Poly operator+(const Poly &, const Poly &);