#include "PolyElement.h"

//==============Constructors=============//
polyElement::polyElement(unsigned int deg)
{
	setDegree(deg);
	setNext(nullptr);
}


//===================Setters==============//
void polyElement::setRational(const Rational& rational){
	_value = rational;

}
void polyElement::setDegree(const int deg){
	_deg = deg;
}
void polyElement::setNext(polyElement* next){
	this->_next = next;
}

//===============Getters==================//
Rational polyElement::getRational() const
{
	return _value;
}

int polyElement::getDegree() const
{
	return _deg;
}

polyElement *polyElement::getNext() const{
	return _next;
}
