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
    //Constructor
	Poly(Rational[], size_t);
	Poly(const int,const Rational&);
	Poly(const Poly &);
	Poly();
	Poly(const Rational &);
    
    //Destrctor
    ~Poly();
    
    //getters
	int deg()const;
	int getNumOfElements()const;
    unsigned int getDbIndex() const;
    Poly gcd(const Poly &);
	
    
    //Operators
    Poly &operator/=(const Rational &);
    Poly &operator*=(const Rational &);
    Poly &operator*=(const Poly &);
    Poly &operator/=(const Poly &);
    Poly &operator+=(const Poly &);
    Poly &operator-=(const Poly &);
    Poly &operator=(const Poly &);
    Rational operator()(const Rational &);
    Rational operator[](const  int);

private:
    Poly findGcd(const Poly &,const Poly &);
	int items = 0;
    unsigned int _DBIndex;
};


//operators
std::ostream &operator<<(std::ostream &, Poly);

//arithmetic
Poly operator+(const Poly &, const Poly &);
Poly operator-(const Poly &, const Poly &);
Poly operator*(const Poly &, const Poly &);
Poly operator/(const Poly &, const Poly &);
Poly operator%(const Poly &, const Poly &);

//logical
bool operator==(const Poly &, const Poly &);
bool operator!=(const Poly &, const Poly &);





