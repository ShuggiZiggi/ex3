#include "DataBase.h"

DataBase __globalDB__ = DataBase();

void DataBase::requestPrintInstance(const unsigned int id){
	_currentForPrint = _DBList[id]._headOfPoly;
}

polyElement DataBase::getNextPrintInstance(bool & success){
	polyElement ElementToReturn;

		ElementToReturn._deg = _currentForPrint->_deg;
		ElementToReturn._value = _currentForPrint->_value;
		ElementToReturn._next = nullptr;

	_currentForPrint = _currentForPrint->_next;

	success = _currentForPrint == nullptr ? false : true;
		

	return ElementToReturn;
}

DataBase::~DataBase(){
	return;
	for (unsigned int i = 0; i < _sizeOfList; i++)
	{
		_clearList(_DBList[i]._headOfPoly);
	}

	delete _DBList;
}

void DataBase::_clearList(polyElement* position){

	if (position == nullptr)
		return;
	_clearList(position->_next);

	delete position;
}

DataBase::DataBase(){
	_DBList = nullptr;
	_sizeOfList = 0;
}

unsigned int DataBase::getNewIndex(){
	_sizeOfList++;
	_increaseList();
	return _sizeOfList - 1;
}

void DataBase::inputNewNode(const unsigned int id, const Rational& val, const unsigned int deg){

	polyElement *newPoly = new polyElement;
	newPoly->_deg = deg;
	newPoly->_value = val;
	
	if (_DBList[id]._headOfPoly != nullptr)
		newPoly->_next = _DBList[id]._headOfPoly;
	else
		newPoly->_next = nullptr;

	_DBList[id]._headOfPoly = newPoly;
}

void  DataBase::_increaseList(){
	polyHead *tmp = new polyHead[_sizeOfList];
	for (unsigned int i = 0; i < _sizeOfList - 1; i++)
		tmp[i]._headOfPoly = _DBList[i]._headOfPoly;

	tmp[_sizeOfList-1]._headOfPoly = nullptr;

	delete[] _DBList;
	_DBList = tmp;

}


polyElement::polyElement(unsigned int deg){
	this->_deg = deg;
	this->_next = nullptr;
}