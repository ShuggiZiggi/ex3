#include "Poly.h"
#include "Rational.h"
#include "DataBase.h"
#include <cmath>
extern DataBase __globalDB__;

//============Constructs================//
/*
    Build Poly from array of coefficients and degree by array index
 */
//============================================//
Poly::Poly(Rational arr[], size_t arrSize){

    _DBIndex = __globalDB__.getNewIndex();

	unsigned int deg = 0;
	
	for (int i = (int)arrSize - 1; i >= 0; i--)
	{
      
		if (arr[i].getNumerator() == 0)
			continue;
        
		deg = (unsigned int)arrSize - i - 1;

		__globalDB__.inputNewNode(_DBIndex, arr[i], deg);
		items++;
	}

	if (!items) //empty Poly
		__globalDB__.inputNewNode(_DBIndex, Rational(), 0);
}

//============================================//
/*
    Build an empty poly - 0
 */
Poly::Poly()
{
    _DBIndex = __globalDB__.getNewIndex();
    items++;
    __globalDB__.inputNewNode(_DBIndex, Rational(), 0);
}

//============================================//
/*
    Build a constant poly  (coefficient *X^0)
 */
Poly::Poly(const Rational & rational){
    _DBIndex = __globalDB__.getNewIndex();
    items++;
    __globalDB__.inputNewNode(_DBIndex, rational, 0);
}

//============================================//
/*
    Build a single element poly (tX^y)
 */
Poly::Poly(const int deg, const Rational& rational)
{
    _DBIndex = __globalDB__.getNewIndex();
    items++;
    __globalDB__.inputNewNode(_DBIndex, rational, deg);
    
}

//============================================//
/*
    Copy Constructor
 */
Poly::Poly(const Poly &original)
{
	_DBIndex = __globalDB__.getNewIndex();
	__globalDB__.cloneListFromIndexToIndex(original.getDbIndex(), _DBIndex);
}


//=================METHODS==============//
int Poly::deg()const{
    
    return __globalDB__.getElementByIndexes(getDbIndex(), 0).getDegree();
}

int Poly::getNumOfElements()const{
    return items;
}

unsigned int Poly::getDbIndex() const{
    return _DBIndex;
}

Poly Poly::gcd(const Poly &polyGcd){
    
    return findGcd(*this,polyGcd);
}

Poly Poly::findGcd(const Poly& L, const Poly& R)
{
    
    // if the divisor is zero, return 0 which is ilegal gcd
    if (R.deg() == 0)
    {
        return Poly(Rational());
    }
    
    // aux Polys. Make a the larger Polynomial forthe process.
    // we'll also make them in absolute value to get a
    // positive gcd.
    Poly a;
    Poly b;
    
    if (L.deg() >= R.deg())
    {
        a = L;
        b = R;
    }
    else
    {
        a = R;
        b = L;
    }
    
    // reminder.
    Poly r = a%b;
    
    while (r.deg() != 0)
    {
        a = b;
        b = r;
        r = a%b;
    }
    
    return b/=Rational(b.deg());
}

//==================OPERATORS=====================//

//===================Print Operator===================//
/*
    Asks from database to create a print instance,
    database will response each time with the next poly element
    until it's the end of the list
 */
std::ostream &operator<<(std::ostream &os, Poly pol){
	
	__globalDB__.requestPrintInstance(pol.getDbIndex());

	bool success = false;
	
	while (true){
		polyElement current = __globalDB__.getNextPrintInstance(success);
        
        Rational temp = current.getRational();
        os << temp;
        if(current.getDegree() != 0)
            os << "X^" << current.getDegree();
		
		if (success)
		{
			os << " + ";
		}
		else
			break;
	}

	return os;
}


//===========Arithmetic Operators ===============//
/*
    + Operator, returns new Poly foreach(ceof in coefficients) coef+=findMatchInPoly2()
 */
Poly operator+(const Poly &L, const Poly &R){
	size_t arraySize = (L.deg() > R.deg()) ? L.deg()+1 : R.deg()+1;
	Rational *rationalPolyArr = new Rational[arraySize];
    
    //set array with 0
	for (int i = 0; i < arraySize; i++)
		rationalPolyArr[i] = 0;
	
	//get num of elements in each poly
	int rSize = R.getNumOfElements();
	int lSize = L.getNumOfElements();
    
    for (int index = 0; index < rSize; index++)
		rationalPolyArr[arraySize - 1 -__globalDB__.getElementByIndexes(R.getDbIndex(), index).getDegree()] += __globalDB__.getElementByIndexes(R.getDbIndex(), index).getRational();

	for (int index = 0; index < lSize; index++)
		rationalPolyArr[arraySize - 1 -__globalDB__.getElementByIndexes(L.getDbIndex(), index).getDegree()] += __globalDB__.getElementByIndexes(L.getDbIndex(), index).getRational();
	
	 Poly temp =  Poly(rationalPolyArr, arraySize);

	 delete[] rationalPolyArr;

	 return temp;
}

/*
 - Operator, returns new Poly foreach(ceof in coefficients) coef-=findMatchInPoly2()
 */
Poly operator-(const Poly &L, const Poly &R){
    
    size_t arraySize = (L.deg() > R.deg()) ? L.deg()+1 : R.deg()+1;
    Rational *rationalPolyArr = new Rational[arraySize];
    
    for (int i = 0; i < arraySize; i++)
        rationalPolyArr[i] = 0;
    
    int rSize = R.getNumOfElements();
    int lSize = L.getNumOfElements();
    
    //first init array with left poly
    for (int index = 0; index < lSize; index++)
        rationalPolyArr[arraySize - 1 -__globalDB__.getElementByIndexes(L.getDbIndex(), index).getDegree()] += __globalDB__.getElementByIndexes(L.getDbIndex(), index).getRational();
    
    //reduce from it right Array
    for (int index = 0; index < rSize; index++)
        rationalPolyArr[arraySize - 1 -__globalDB__.getElementByIndexes(R.getDbIndex(), index).getDegree()] -= __globalDB__.getElementByIndexes(R.getDbIndex(), index).getRational();
    
    Poly temp =  Poly(rationalPolyArr, arraySize);
    
    delete[] rationalPolyArr;
    
    return temp;
}

/*
 += Operator, same as + but local
 */
Poly &Poly::operator+=(const Poly &L)
{
    *this = *this + L;
    
    return *this;
}

/*
 -= Operator, same as - but local
 */
Poly &Poly::operator-=(const Poly &L)
{
    *this = *this - L;
    
    return *this;
}

/*
    * operators, return L * R
 */
Poly operator*(const Poly & L, const Poly & R){
    
    size_t arraySize = L.deg() + R.deg();
        arraySize++;
    
    Rational *rationalPolyArr = new Rational[arraySize];
    
    for (int i = 0; i < arraySize; i++)
        rationalPolyArr[i] = 0;

    int rSize = R.getNumOfElements();
    int lSize = L.getNumOfElements();
    
   
    for(int rElement = rSize -1; rElement >= 0; --rElement)
    {
        polyElement currentRight = __globalDB__.getElementByIndexes(R.getDbIndex(), rElement);
        
               for(int lElement = lSize -1; lElement >= 0; --lElement)
        {
           
            polyElement currentLeft = __globalDB__.getElementByIndexes(L.getDbIndex(), lElement);
            
            Rational mult = currentLeft.getRational() * currentRight.getRational();
            rationalPolyArr[arraySize -1 - (currentRight.getDegree() + currentLeft.getDegree())] += mult;
            
        }
    }
   
    Poly temp = Poly(rationalPolyArr,arraySize);
    
    delete [] rationalPolyArr;
    return temp;
}

// Mod Operator


Poly &Poly::operator*=(const Rational &mul){
    
    for(int i=0; i < items; i++)
    {
        __globalDB__.replaceRationalValue_findBySubIndex(getDbIndex(),i, __globalDB__.getElementByIndexes(getDbIndex(), i).getRational() * mul);
    }
    
    return *this;
}

Poly &Poly::operator=(const Poly &toCopy){
    __globalDB__.cloneListFromIndexToIndex(toCopy.getDbIndex(), getDbIndex());
    
    this->items = toCopy.getNumOfElements();
    
    return *this;
}

Poly &Poly::operator*=(const Poly &mul){
    *this = *this * mul;
    
    return *this;
}

Poly &Poly::operator/=(const Poly &div){
    *this = *this / div;
    
    return *this;
}


Poly operator%(const Poly &L, const Poly &R){
    
    if(L == R)
        return Poly(0);
    
    return ((L - R*(L/R)));
}

// Poly / Poly Operator
Poly operator/(const Poly & L, const Poly & R){
    
    Rational lVal = __globalDB__.getElementByIndexes(L.getDbIndex(), 0).getRational();
    Rational rVal = __globalDB__.getElementByIndexes(R.getDbIndex(), 0).getRational();
    
    Rational div = lVal/rVal;
    //Store The Result Poly
    Poly resultPoly(L.deg() - R.deg(),div);
    
    //current Poly to be divided
    Poly currentResult = L - (resultPoly * R);
    
    while(currentResult.deg() >= R.deg())
    {
        __globalDB__.inputNewNode(resultPoly.getDbIndex(), __globalDB__.getElementByIndexes(currentResult.getDbIndex(), 0).getRational() / rVal, currentResult.deg()-R.deg());
        
        currentResult = currentResult - (resultPoly * R);
    }
    
    return resultPoly;
}

//return value at given x
Rational Poly::operator()(const Rational & x){
    
    polyElement currentElement;
    //set current result to 0, and add to it values in loop
    Rational result(0,0);
    
    for(int elemIndex=0; elemIndex < items; ++elemIndex)
    {
        currentElement = __globalDB__.getElementByIndexes(getDbIndex(),elemIndex);
        int newNumerator = pow(x.getNumerator(),currentElement.getDegree());
        int newDenomerator = pow(x.getDenominator(),currentElement.getDegree());
        result+=Rational(newNumerator,newDenomerator) * currentElement.getRational();
    }
    
    return result;
}

//get a degree by
Rational Poly::operator[](const  int degree){
    if(degree > deg())
    {
        std::cerr << "No Element With Degree " << degree;
        return Rational();
    }

    
    for(int elemIndex=0; elemIndex < items; ++elemIndex)
    {
        if( __globalDB__.getElementByIndexes(getDbIndex(),elemIndex).getDegree() == degree)
            return __globalDB__.getElementByIndexes(getDbIndex(),elemIndex).getRational();
    }
    
    return Rational();
}

//================Logical Operators=========//
bool operator==(const Poly &L, const Poly &R)
{
    if(L.deg() != R.deg())
        return false;
    
    if(L.getNumOfElements() != R.getNumOfElements())
        return false;
    
   
    int rSize = R.getNumOfElements();
    int lSize = L.getNumOfElements();
    
    
    for(int rElement = rSize -1; rElement >= 0; --rElement)
    {
        polyElement currentRight = __globalDB__.getElementByIndexes(R.getDbIndex(), rElement);
        bool matchFound = false;
        
        for(int lElement = lSize -1; lElement >= 0; --lElement)
        {
            polyElement currentLeft = __globalDB__.getElementByIndexes(L.getDbIndex(), lElement);
            
            if(currentLeft.getDegree() == currentRight.getDegree() && currentLeft.getRational() == currentRight.getRational())
            {
                matchFound = true;
                break;
            }
            
        }
        
        if(!matchFound)
            return false;
    }
    
    return true;
}

bool operator!=(const Poly &L, const Poly &R)
{
    return !(L==R);
}


Poly &Poly::operator/=(const Rational &div){
    
    for(int i=0; i < items; i++)
    {
        __globalDB__.replaceRationalValue_findBySubIndex(getDbIndex(),i, __globalDB__.getElementByIndexes(getDbIndex(), i).getRational() / div);
    }
    
    return *this;
}




//default destructor
Poly::~Poly(){}
