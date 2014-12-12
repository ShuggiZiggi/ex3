#include "DataBase.h"
#include "polyElement.h"
DataBase __globalDB__ = DataBase();

void DataBase::requestPrintInstance(const unsigned int id){
	_currentForPrint = _DBList[id]._headOfPoly;
}

polyElement DataBase::getNextPrintInstance(bool & success){
	polyElement ElementToReturn;

	ElementToReturn.setDegree(_currentForPrint->getDegree());
	ElementToReturn.setRational(_currentForPrint->getRational());

	success = _currentForPrint->getNext() == nullptr ? false : true;

	_currentForPrint = _currentForPrint->getNext();

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
	_clearList(position->getNext());

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

	std::cout << "My Poly Id: " << id << std::endl;
	polyElement *newPoly = new polyElement();
	newPoly->setDegree(deg);
	newPoly->setRational(val);
	//std::cout << id << std::endl;
	//std::cout << _DBList << std::endl;
	std::cout << "Head of list: " << std::endl;
	std::cout << _DBList[id]._headOfPoly << std::endl;

	if (_DBList[id]._headOfPoly == nullptr)
		newPoly->setNext(nullptr);
	else
		newPoly->setNext(_DBList[id]._headOfPoly);
	std::cout << "Next Value is: " << newPoly->getNext() << std::endl;
	std::cout << "My Degree Value is: " << newPoly->getDegree() << std::endl;
	_DBList[id]._headOfPoly = newPoly;
}

void  DataBase::_increaseList(){
	
	polyHead *tmp = new polyHead[_sizeOfList];
	
	system("pause");
	for (unsigned int i = 0; i < _sizeOfList - 1; i++)
		tmp[i]._headOfPoly = _DBList[i]._headOfPoly;

	tmp[_sizeOfList-1]._headOfPoly = nullptr;

	if (_DBList != nullptr)
		delete[] _DBList;

	_DBList = tmp;

}

void DataBase::cloneListFromIndexToIndex(const int original, const int newToClone){
	polyElement *currentPosition = _DBList[original]._headOfPoly;

	while (currentPosition != nullptr)
	{
		inputNewNode(newToClone, currentPosition->getRational(), currentPosition->getDegree());
		currentPosition = currentPosition->getNext();
	}
}

polyElement DataBase::getElementByIndexes(const int DBindex, const int element) const{
	
	polyElement *currentPosition = _DBList[DBindex]._headOfPoly;
	for (int current = 0; current <= DBindex && current < _sizeOfList; current++)
		currentPosition = currentPosition->getNext();

	return *currentPosition;
}
