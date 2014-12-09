#pragma once
#include <stdlib.h>
#include <iosfwd>
#include <ostream>
#include <iostream>
#include <cstddef>

#include "Rational.h"
#include "DataBase.h"

class Poly
{
public:
	Poly(Rational[], size_t);
	unsigned int getDbIndex() const{
		return _DBIndex;
	}
	~Poly();

private:
	int items = 0;
	unsigned int _DBIndex;
};

std::ostream &operator<<(std::ostream &, Poly);