#pragma once

#include "Rational.h"

//Poly Element class
//holds each poly element's inside
//linked list
class polyElement {
public:
    //constructor
	polyElement(unsigned int = 0);
    
    //setters
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

