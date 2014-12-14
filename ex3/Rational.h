#pragma once

#include <stdlib.h>
#include <iosfwd>
#include <iostream>


class Rational
{
public:
    //constructors
    Rational(int = 0, int = 1);
    //desturctor -  Default
    ~Rational();
    
    //getters
	int getNumerator() const;
	int getDenominator() const;
	Rational getInverseFragment() const;

    //Operators
	Rational& operator+=(const Rational&);
	Rational& operator-=(const Rational&);
	Rational& operator*=(const Rational&);
	Rational& operator/=(const Rational&);
	Rational& operator++();
	Rational& operator--();
	

private:
	int findGCD(const int, const int) const;
	void fixSigned();
	int _numerator; //mone
	int _denominator; //mechane
};

//Global Operators
//Arithmetic
Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);
//Logical
bool operator==(const Rational& a, const Rational& b);
bool operator!=(const Rational& a, const Rational& b);
bool operator<(const Rational& a, const Rational& b);
bool operator>(const Rational& a, const Rational& b);
bool operator<=(const Rational& a, const Rational& b);
bool operator>=(const Rational& a, const Rational& b);
//Print
std::ostream& operator << (std::ostream&, Rational&);