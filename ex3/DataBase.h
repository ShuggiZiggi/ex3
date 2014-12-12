#pragma once

#include "Rational.h"
#include "PolyElement.h"

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
	void cloneListFromIndexToIndex(const int, const int);
	polyElement getElementByIndexes(const int, const int) const;
	
private:
	polyElement *_currentForPrint;
	void _clearList(polyElement*);
	polyHead *_DBList;
	unsigned int _sizeOfList;
	
	void _increaseList();
};



