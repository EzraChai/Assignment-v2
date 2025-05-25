#ifndef DIET_H
#define DIET_H
#include <string>

class Diet
{
private:
    std::string mealType; // e.g., breakfast, lunch, dinner
    std::string food;     // e.g., salad, chicken, rice
    int calories;         // calories of the food
public:
    Diet();
    Diet(std::string, std::string, int);
    ~Diet();

    std::string getMealType() const;
    std::string getFood() const;
    int getCalories() const;

    void displayDiet() const;

    Diet operator+(const Diet &otherDiet) const;
};

#endif