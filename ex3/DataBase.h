#pragma once

#include "Rational.h"
#include "PolyElement.h"

struct polyHead {
	polyElement *_headOfPoly;
};

class DataBase
{
public:
    //Constructors || destructor
    DataBase();
    ~DataBase();
    
    //getters
    polyElement getNextPrintInstance(bool &); //non const, sets the _currentForPrint
    unsigned int getNewIndex(); //non const, generates new id
    polyElement getElementByIndexes(const int, const int) const;
    
	//other Methods
    void requestPrintInstance(const unsigned int);
	void inputNewNode(const unsigned int, const Rational&, const unsigned int);
	void cloneListFromIndexToIndex(const int, const int);
    void replaceRationalValue_findBySubIndex(const int,const int,const Rational &);
	
private:
	polyElement *_currentForPrint;
	polyHead *_DBList;
	unsigned int _sizeOfList;
    
	void _clearList(polyElement*);
	void _increaseList();
};



