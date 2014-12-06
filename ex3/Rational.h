#pragma once

#include <stdlib.h>
#include <iosfwd>
#include <iostream>

class Rational
{


public:
	Rational::Rational(int = 0, int = 1);
	int getNumerator() const;
	int getDenominator() const;
	Rational getInverseFragment() const;

	Rational& operator+=(const Rational&);
	Rational& operator-=(const Rational&);
	Rational& operator*=(const Rational&);
	Rational& operator/=(const Rational&);
	Rational& operator++();
	Rational& operator--();
	~Rational();

private:
	int findGCD(const int, const int) const;
	void fixSigned();
	int _numerator; //mone
	int _denominator; //mechane
};

Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);
bool operator==(const Rational& a, const Rational& b);
bool operator!=(const Rational& a, const Rational& b);
bool operator<(const Rational& a, const Rational& b);
bool operator>(const Rational& a, const Rational& b);
bool operator<=(const Rational& a, const Rational& b);
bool operator>=(const Rational& a, const Rational& b);
std::ostream& operator << (std::ostream&, Rational&);