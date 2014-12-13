#include "PolyElement.h"


polyElement::polyElement(unsigned int deg)
{
	setDegree(deg);
	std::cout << "========\n";
	setNext(nullptr);
	std::cout << "========\n";
}

void polyElement::setRational(const Rational& rational){
	_value = rational;

}
void polyElement::setDegree(const int deg){
	_deg = deg;
}
void polyElement::setNext(polyElement* next){
	this->_next = next;
	std::cout << "IM INSIDE THE  FUCkTION\n" << next << "\n";
}

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
