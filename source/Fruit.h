//------------------------------------------------------------------------------
// Fruit.h : declaration and definition file for
//      - base class Fruit
//      - derived classes Orange, Banana
//------------------------------------------------------------------------------
#pragma once
//#define LC_DEBUG

#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cout;
using std::ostream;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int _FRUIT = 0;
// keep derived class id's alphabetical
constexpr int BANANA = 1;
constexpr int ORANGE = 2;

//------------------------------------------------------------------------------
// Fruit
//------------------------------------------------------------------------------
class Fruit {
    friend ostream& operator<<(ostream& os, Fruit& f);

private:
    // use static member variable to count instances
    static int instanceCount;

    // each instance gets a unique ID
    int instanceID;

    // identify instance type
    int fruitID;

    // fruit data
    int calories;
    string color;

public:
    // constructors
    Fruit(int _fruitID, string _color) {
        instanceID = ++instanceCount;
        fruitID = _fruitID;
        calories = 0;
        color = _color;
    }

    Fruit() : Fruit(_FRUIT, "none") { }

    // getters
    static int getInstanceCount() { return instanceCount; }
    int getInstanceID() const { return instanceID; }
    int getFruitID() const { return fruitID; }
    int getCalories() const { return calories; }
    const string& getColor() const { return color; }

    // setter
    void setCalories(int _calories) { calories = _calories; }

    // overload + operator to add calories of two Fruit instances
    int operator+(Fruit& rhs) {
        return this->calories + rhs.calories;
    }

#ifdef LC_DEBUG
    ~Fruit() { cout << "Fruit destructor\n"; }
#endif
};

//------------------------------------------------------------------------------
// Orange
//------------------------------------------------------------------------------
class Orange : public Fruit {
public:
    Orange() : Fruit::Fruit(ORANGE, "orange") { setCalories(60); }

#ifdef LC_DEBUG
    ~Orange() { cout << "Orange destructor\n"; }
#endif
};

//------------------------------------------------------------------------------
// Banana
//------------------------------------------------------------------------------
class Banana : public Fruit {
public:
    Banana() : Fruit::Fruit(BANANA, "yellow") { setCalories(90); }

#ifdef LC_DEBUG
    ~Banana() { cout << "Banana destructor\n"; }
#endif
};

//------------------------------------------------------------------------------
// - allocate space for and initialize static member vars outside the class
// - for multi-compilation unit projects, put this declaration/initialization
// either:
//      - in a separate .cpp file (named Fruit_statics.cpp, e.g.), or
//      - in your app code
//------------------------------------------------------------------------------
int Fruit::instanceCount = 0;

//------------------------------------------------------------------------------
// operator << overload
//  - static avoids link errors when > 1 compilation units
//------------------------------------------------------------------------------
static ostream& operator<<(ostream& os, Fruit& f) {

    // here static means the data values will persist across function calls 
    static const string fruitNames[] = { "Fruit ", "Banana ", "Orange " };

    os << "Calories for " << fruitNames[f.fruitID] << f.calories;

    return os;
}
