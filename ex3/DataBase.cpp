#include "DataBase.h"
#include "polyElement.h"

//set a global DB,
//We want the program to generate a single Database
//to manage all the polynoms
DataBase __globalDB__ = DataBase();

//===========Constructor==============//
DataBase::DataBase(){
    _DBList = nullptr;
    _sizeOfList = 0;
}

//==============Destructor============//
DataBase::~DataBase(){
    
    for (unsigned int i = 0; i < _sizeOfList; i++)
        _clearList(_DBList[i]._headOfPoly);
    
    
    delete _DBList;
}
//=====Sub Destructor List===//
void DataBase::_clearList(polyElement* position){
    
    if (position == nullptr)
        return;
    _clearList(position->getNext());
    
    delete position;
}

//========================================//
void DataBase::requestPrintInstance(const unsigned int id){
	_currentForPrint = _DBList[id]._headOfPoly;
}
//========================================//
polyElement DataBase::getNextPrintInstance(bool & success){
	polyElement ElementToReturn;

	ElementToReturn.setDegree(_currentForPrint->getDegree());
	ElementToReturn.setRational(_currentForPrint->getRational());

	success = _currentForPrint->getNext() == nullptr ? false : true;

	_currentForPrint = _currentForPrint->getNext();

	return ElementToReturn;
}

//========================================//

unsigned int DataBase::getNewIndex(){
	_sizeOfList++;
	_increaseList();
	return _sizeOfList - 1;
}
//========================================//

void DataBase::inputNewNode(const unsigned int id, const Rational& val, const unsigned int deg){

	polyElement *newPoly = new polyElement();
	newPoly->setDegree(deg);
	newPoly->setRational(val);

	if (_DBList[id]._headOfPoly == nullptr)
		newPoly->setNext(nullptr);
	else
		newPoly->setNext(_DBList[id]._headOfPoly);
    
	_DBList[id]._headOfPoly = newPoly;
}
//========================================//

void  DataBase::_increaseList(){
	
	polyHead *tmp = new polyHead[_sizeOfList];
	
	for (unsigned int i = 0; i < _sizeOfList - 1; i++)
		tmp[i]._headOfPoly = _DBList[i]._headOfPoly;

	tmp[_sizeOfList-1]._headOfPoly = nullptr;

	if (_DBList != nullptr)
		delete[] _DBList;

	_DBList = tmp;

}
//========================================//

void DataBase::cloneListFromIndexToIndex(const int original, const int newToClone){
	polyElement *currentPosition = _DBList[original]._headOfPoly;
    
    //clean old list
    _clearList(_DBList[newToClone]._headOfPoly);
    _DBList[newToClone]._headOfPoly = nullptr;
    
	while (currentPosition != nullptr)
	{
		inputNewNode(newToClone, currentPosition->getRational(), currentPosition->getDegree());
		currentPosition = currentPosition->getNext();
	}
}
//========================================//

polyElement DataBase::getElementByIndexes(const int DBindex, const int element) const{
	
	polyElement *currentPosition = _DBList[DBindex]._headOfPoly;
	for (int current = 0; current < element && current < _sizeOfList; current++)
		currentPosition = currentPosition->getNext();

	return *currentPosition;
}
//========================================//

void DataBase::replaceRationalValue_findBySubIndex(const int index,const int subIndex,const Rational &newVal){
    polyElement *currentPosition =  _DBList[index]._headOfPoly;
    
    int counter = 0;
    while(true)
    {
        if(currentPosition == nullptr)
            return;
        
        if(counter == subIndex)
        {
            currentPosition->setRational(newVal);
            return;
        }
        
        currentPosition = currentPosition->getNext();
        counter++;
        
            
    }
}
