#include "Diet.h"
#include <iostream>

/*
    Default constructor
*/
Diet::Diet() : mealType(""), food(""), calories(0)
{
}

/*
    Overloading constructor
*/
Diet::Diet(std::string mt, std::string f, int c) : mealType(mt), food(f), calories(c) {}

/*
    Destructor
*/
Diet::~Diet() {}

/*
    Display the details of the diet
*/
void Diet::displayDiet() const
{
    std::cout << "Meal Type: " << mealType << std::endl;
    std::cout << "Food: " << food << std::endl;
    std::cout << "Calories: " << calories << std::endl;
}

/*
    Get food type
*/
std::string Diet::getMealType() const
{
    return mealType;
}

/*
    Get food name
*/
std::string Diet::getFood() const
{
    return food;
}

/*
    Get calories of the food
*/
int Diet::getCalories() const
{
    return calories;
}

/*
    Operator overloading +
    add the total calories together
*/
Diet Diet::operator+(const Diet &otherDiet) const
{
    return Diet(mealType, food + " + " + otherDiet.getFood(), calories + otherDiet.getCalories());
}