//------------------------------------------------------------------------------
// Fruit_.cpp
//      - static member variables
//      - friend operator overload functions
// 
// separate file avoids link errors and duplicate symbols in projects with
// multiple compilation units
//------------------------------------------------------------------------------
#include "Fruit.h"

#include <iostream>
using std::ostream;

//------------------------------------------------------------------------------
// allocate space for and initialize static member vars outside the class
//------------------------------------------------------------------------------
int Fruit::instanceCount = 0;

//------------------------------------------------------------------------------
// friend operator << overload
//------------------------------------------------------------------------------
ostream& operator<<(ostream& os, Fruit& f) {

    // "local static" means a value will persist across function calls 
    static const string fruitNames[] = { "Fruit ", "Banana ", "Orange " };

    os << "Calories for " << fruitNames[f.fruitID] << f.calories;
    return os;
}
