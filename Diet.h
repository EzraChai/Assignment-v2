#ifndef DIET_H
#define DIET_H
#include <string>

class Diet
{
    private:
        std::string mealType; // e.g., breakfast, lunch, dinner
        std::string food; // e.g., salad, chicken, rice
        int calories; // calories in the food item
    public:
        Diet();
        Diet(std::string, std::string, int);
        void displayDiet() const;
        Diet operator +(const Diet& otherDiet) const;
};

#endif