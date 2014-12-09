#pragma once
#include "Rational.h"



//====STRUCT====//
struct polyElement {
	polyElement(unsigned int = 0);
	Rational _value;
	unsigned int _deg;
	polyElement *_next;
};

struct polyHead {
	polyElement *_headOfPoly;
};

class DataBase
{
public:
	unsigned int getNewIndex();
	void inputNewNode(const unsigned int, const Rational&, const unsigned int);
	DataBase();
	~DataBase();
	void requestPrintInstance(const unsigned int);
	polyElement getNextPrintInstance(bool &);
	
private:
	polyElement *_currentForPrint;
	void _clearList(polyElement*);
	polyHead *_DBList;
	unsigned int _sizeOfList;
	
	void _increaseList();
};



