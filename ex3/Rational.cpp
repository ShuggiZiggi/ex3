#include "Rational.h"

#include <ostream>

int Rational::getNumerator() const{
	return _numerator;
}

int Rational::getDenominator() const{
	return _denominator;
}

int Rational::findGCD(const int a, const int b) const{

	if (a == 0) return b;
	return abs (findGCD(b%a, a));
}

Rational Rational::getInverseFragment() const{

	return _numerator ?  Rational(_denominator, _numerator) : (*this);
}

Rational::Rational(int numerator, int denominator){

	int gcd = findGCD(numerator, denominator);

	_numerator = gcd > 1 ? numerator / gcd : numerator;
	_denominator = gcd > 1 ? denominator / gcd : denominator;

	fixSigned();
}

void Rational::fixSigned(){
	double div = (double)_numerator / _denominator;

	if (div < 0) //one is minus and one is plus
		_numerator = _numerator < 0 ? _numerator : -_numerator;
	else
		_numerator = abs(_numerator);

	_denominator = _numerator ?  abs(_denominator) : 1;
}

Rational operator+(const Rational& a, const Rational& b){

	return Rational((a.getNumerator() * b.getDenominator()) + (a.getDenominator() * b.getNumerator()),
		(a.getDenominator() * b.getDenominator()));
}

Rational operator-(const Rational& a, const Rational& b){

	return Rational((a.getNumerator() * b.getDenominator()) - (a.getDenominator() * b.getNumerator()),
		(a.getDenominator() * b.getDenominator()));
}

Rational operator*(const Rational& a, const Rational& b){

	return Rational((a.getNumerator() * b.getNumerator()),
		(a.getDenominator() * b.getDenominator()));
}

Rational operator/(const Rational& a, const Rational& b){

	Rational c = b.getInverseFragment();

	return Rational(a.getNumerator() * c.getNumerator(),
		a.getDenominator() * c.getDenominator());
}

Rational& Rational::operator+=(const Rational& a){

	Rational tmp = (*this) + a;
	
	(*this)._numerator   = tmp.getNumerator();
	(*this)._denominator = tmp.getDenominator();

	return *this;
}

Rational& Rational::operator-=(const Rational& a){

	Rational tmp = (*this) - a;

	(*this)._numerator = tmp.getNumerator();
	(*this)._denominator = tmp.getDenominator();

	return *this;
}

Rational& Rational::operator*=(const Rational& a){

	Rational tmp = (*this) * a;

	(*this)._numerator = tmp.getNumerator();
	(*this)._denominator = tmp.getDenominator();

	return *this;
}

Rational& Rational::operator/=(const Rational& a){

	Rational tmp = (*this) / a;

	(*this)._numerator = tmp.getNumerator();
	(*this)._denominator = tmp.getDenominator();

	return *this;
}

Rational& Rational::operator++(){

	Rational tmp = (*this) + 1;

	(*this)._numerator = tmp.getNumerator();
	(*this)._denominator = tmp.getDenominator();

	return *this;
}

Rational& Rational::operator--(){

	Rational tmp = (*this) - 1;

	(*this)._numerator = tmp.getNumerator();
	(*this)._denominator = tmp.getDenominator();

	return *this;
}

bool operator==(const Rational& a, const Rational& b){

	return a.getNumerator() == b.getNumerator() && a.getDenominator() == b.getDenominator();
}

bool operator!=(const Rational& a, const Rational& b){

	return !(a==b);
}

bool operator<(const Rational& a, const Rational& b){

	return (a - b).getNumerator() < 0;
}

bool operator>(const Rational& a, const Rational& b){

	return (a - b).getNumerator() > 0;
}

bool operator<=(const Rational& a, const Rational& b){

	return (a - b).getNumerator() <= 0;
}

bool operator>=(const Rational& a, const Rational& b){

	return (a - b).getNumerator() >= 0;
}

std::ostream& operator << (std::ostream& os, Rational& a){
	os << a.getNumerator() << '/' << a.getDenominator();
	return os;
}

Rational::~Rational()
{
}
