#include "Diet.h"
#include <iostream>

Diet::Diet() : mealType(""), food(""), calories(0) {}
Diet::Diet(std::string mt, std::string f, int c) : mealType(mt), food(f), calories(c) {}
void Diet::displayDiet() const
{
    std::cout << "Meal Type: " << mealType << std::endl;
    std::cout << "Food: " << food << std::endl;
    std::cout << "Calories: " << calories << std::endl;
}

std::string Diet::getMealType() const
{
    return mealType;
}
std::string Diet::getFood() const
{
    return food;
}
int Diet::getCalories() const
{
    return calories;
}

Diet Diet::operator+(const Diet &otherDiet) const
{
    return Diet(mealType, food + " + " + otherDiet.food, calories + otherDiet.calories);
}