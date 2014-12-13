#pragma once

#include "Rational.h"

class polyElement {
public:
	polyElement(unsigned int = 0);

	void setRational(const Rational&);
	void setDegree(const int);
	void setNext(polyElement*);
	//getters
	Rational getRational() const;
	int getDegree() const;
	polyElement *getNext() const;


private:
	Rational _value;
	int _deg;
	polyElement *_next;
};

