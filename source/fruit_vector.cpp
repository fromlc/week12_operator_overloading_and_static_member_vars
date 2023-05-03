//------------------------------------------------------------------------------
// fruit_vector.cpp 
//
// Demos vector that
//	- uses vector of pointers to base class Fruit instances
//	- vector can store pointers to derived class and base class instances
//	- member variable fruitID identifies instance type: _FRUIT, ORANGE, BANANA
//------------------------------------------------------------------------------
#include "Fruit.h"

#include <algorithm>	// std::sort()
#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cout;
using std::string;
using std::vector;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
vector<FruitPtr>* getFruitVector();
void sortFruits(vector<FruitPtr>*, bool ascending = true);
void displayFruits(vector<FruitPtr>*);
void countCalories();
void deleteFruits(vector<FruitPtr>*&);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

	vector<FruitPtr>* pVFruits = getFruitVector();

	// demo std::sort() with FruitPtr operator < overload
	sortFruits(pVFruits, true);
	displayFruits(pVFruits);

	// demo std::sort() with function pointer param=vSortDown
	sortFruits(pVFruits, false);
	displayFruits(pVFruits);

	// demo operator + overload
	countCalories();

	deleteFruits(pVFruits);

	// very inefficient but convenient way to keep app window open
	system("pause");

	return 0;
}

//------------------------------------------------------------------------------
// - instantiate classes derived from Fruit
// - store instance pointers in new vector<Fruit>
// - return pointer to new vector<Fruit>
//------------------------------------------------------------------------------
vector<FruitPtr>* getFruitVector() {

	// tell C++ we'll store pointers to base class instances
	vector<FruitPtr>* pV = new vector<FruitPtr>;

	// we can store base class pointers too
	pV->push_back(FruitPtr(new Fruit));

	// store pointers to derived class instances instead
	// there are different ways to do this...
	Orange* pOrange = new Orange;
	pV->push_back(FruitPtr(pOrange));
	pV->push_back(FruitPtr(new Orange));
	pV->push_back(FruitPtr(new Banana));

	// we can store base class pointers too
	pV->push_back(FruitPtr(new Fruit));

	// use static member function to report instance count
	cout << "Created " << Fruit::getInstanceCount()
		<< " Fruit instances\n\n";
	
	return pV;
}

//------------------------------------------------------------------------------
// called by std::sort()
//------------------------------------------------------------------------------
bool vSortDown(FruitPtr& lhs, FruitPtr& rhs) {
	return rhs.pFruit->getFruitID() < lhs.pFruit->getFruitID();
}

//------------------------------------------------------------------------------
// std::sort() vector by element fruitID
//------------------------------------------------------------------------------
void sortFruits(vector<FruitPtr>* pV, bool ascending) {

	if (ascending) {
		cout << "sorting derived class ID in ascending order\n";
		std::sort(pV->begin(), pV->end());
	}
	else {
		cout << "sorting derived class ID in descending order\n";
		std::sort(pV->begin(), pV->end(), vSortDown);
	}
}

//------------------------------------------------------------------------------
// display vector elements
//------------------------------------------------------------------------------
void displayFruits(vector<FruitPtr>* pV) {

	// traverse vector of pointers with range-based for loop
	for (FruitPtr& f : *pV) {

		// determine which type this instance was instantiated with
		int fruitID = f.pFruit->getFruitID();

		cout << "Derived class ID " << f.pFruit->getFruitID() << ": ";

		if (fruitID == ORANGE) {
			// must typecast to display Orange's member variable values

			// C++ best-practice way to typecast - static_cast is easy to search for
			Orange* pOrange = static_cast<Orange*>(f.pFruit);

			// C way to typecast - it's hard to find C-style casts in source code!
			// Orange* pOrange = (Orange*)p;

			cout << "Oranges yield " << pOrange->getJuiceYield()
				<< " ounces of juice.\n";
		}
		else if (fruitID == BANANA) {
			// C way to typecast - it's hard to search source code for these
			// Banana* pBanana = (Banana*)p;

			// Use Fruit* p to display base class member variables
			cout << "Bananas are " << f.pFruit->getColor() << '\n';
		}
		else if (fruitID == _FRUIT) {
			cout << "Fruits have " << f.pFruit->getColor() << '\n';
		}

		// getColor() returns a const reference to prevent mutating private color
		//string test = p->getColor();
		//&test = "blue";	// won't compile
	}
	cout << '\n';
}

//------------------------------------------------------------------------------
// - delete vector elements
// - delete vector and set passed reference pointer to nullptr
//------------------------------------------------------------------------------
void deleteFruits(vector<FruitPtr>*& pV) {

	// traverse vector of pointers with iterator this time
	for (auto it = pV->begin(); it != pV->end(); ++it) {
		delete it->pFruit;
	}

	delete pV;
	pV = nullptr;
}

//------------------------------------------------------------------------------
// demo operator + overload for Fruit instances
//------------------------------------------------------------------------------
void countCalories() {
	Banana b;
	Orange o;
	Fruit f;

	//cout << "Calories for Banana: " << b.getCalories() << '\n';
	//cout << "Calories for Orange: " << o.getCalories() << '\n';
	//cout << "Calories for Fruit: " << f.getCalories() << '\n';

	// replace above cout's with operator overload function for <<
	cout << b << '\n';
	cout << o << '\n';
	cout << f << '\n';

	int totalCalories = b + o;

	cout << "Total calories for Banana + Orange: "
		<< totalCalories << "\n\n";
}
