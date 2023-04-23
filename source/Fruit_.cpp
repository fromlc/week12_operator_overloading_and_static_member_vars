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
int Fruit::s_instanceCount = 0;

//------------------------------------------------------------------------------
// friend operator << overload
//------------------------------------------------------------------------------
ostream& operator<<(ostream& os, const Fruit& f) {

    // "local static" means a value will persist across function calls
    // this works well here since we only need to initialize this array once
    static const string fruitNames[] = { "Fruit ", "Banana ", "Orange " };

    os << "Calories for " << fruitNames[f.fruitID] << f.calories;
    return os;
}
