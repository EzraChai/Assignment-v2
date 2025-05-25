#include "Person.h"
#include <string>
#include <iomanip>
#include <iostream>

/*
    Default constructor
*/
Person::Person() : name(""), age(1), gender(""), weight(0.0), height(0.0), activityLevel(0)
{
}

/*
    Overloading constructor
*/
Person::Person(std::string n, int a, std::string ge, double w, double h) : name(n), age(a), gender(ge), weight(w), height(h), activityLevel(0)
{
}

/*
    Default destructor
*/
Person::~Person() {}

/*
    Set the name of the person
*/
void Person::setName(std::string n)
{
    name = n;
}

/*
    Set the age of the person
*/
void Person::setAge(int a)
{
    if (a <= 0 || a > 150)
    {
        return;
    }
    age = a;
}

/*
    Set the gender the person
*/
void Person::setGender(std::string ge)
{
    if (ge != "M" && ge != "F")
    {
        return;
    }
    gender = ge;
}

/*
    Set the weight of the person
*/
void Person::setWeight(double w)
{
    if (w <= 0)
    {
        return;
    }
    weight = w;
}

/*
    Set the height of the person
*/
void Person::setHeight(double h)
{
    if (h <= 0 || h > 10.0)
    {
        return;
    }
    height = h;
}

/*
    Get the name of the person
*/
std::string Person::getName() const
{
    return name;
}

/*
    Get the age of the person
*/
int Person::getAge() const
{
    return age;
}

/*
    Get the gender of the person
*/
std::string Person::getGender() const
{
    return gender;
}

/*
    Get the weight of the person
*/
double Person::getWeight() const
{
    return weight;
}

/*
    Get the height of the person
*/
double Person::getHeight() const
{
    return height;
}

/*
    Get the activity level of the person
*/
int Person::getActivityLevel() const
{
    return activityLevel;
}

/*
    Calculate the BMI of the person
*/
double Person::calculateBMI() const
{
    if (height > 0)
    {
        return weight / (height * height);
    }
    return 0.0; // Avoid division by zero
}

/*
    Calculate the BMR of the person
*/
double Person::calculateBMR() const
{
    if (gender == "M")
    {
        return 10 * weight + 6.25 * (height * 100) - 5 * age + 5; // Calculation BMR for Men
    }
    else if (gender == "F")
    {
        return 10 * weight + 6.25 * (height * 100) - 5 * age - 161; // Calculation BMR for Women
    }
    return 0.0;
}

/*
    Calculate the TDEE of the person
*/
double Person::calculateTDEE() const
{
    double bmr = calculateBMR();
    if (activityLevel == 1)
    {
        return bmr * 1.2; // Sedentary
    }
    else if (activityLevel == 2)
    {
        return bmr * 1.375; // Lightly active
    }
    else if (activityLevel == 3)
    {
        return bmr * 1.55; // Moderately active
    }
    else if (activityLevel == 4)
    {
        return bmr * 1.725; // Very active
    }
    else if (activityLevel == 5)
    {
        return bmr * 1.9; // Super active
    }
    return bmr; // Default to BMR if no activity level is set
}

/*
    Prompt user for activity level
*/
void Person::promptUserForActivityLevel()
{
    int activityLevel;

    // Display activity level options
    std::cout << "\n------------ Activity Level ------------" << std::endl;
    std::cout << "Select your activity level (1-5):" << std::endl;
    std::cout << "1. Sedentary (little or no exercise)" << std::endl;
    std::cout << "2. Lightly active (light exercise/sports 1-3 days/week)" << std::endl;
    std::cout << "3. Moderately active (moderate exercise/sports 3-5 days/week)" << std::endl;
    std::cout << "4. Very active (hard exercise/sports 6-7 days a week)" << std::endl;
    std::cout << "5. Super active (very hard exercise & physical job or 2x training)" << std::endl;
    std::cout << "Please enter your activity level: ";
    std::cin >> activityLevel;

    // Validate activity level input
    while (activityLevel < 1 || activityLevel > 5)
    {
        std::cout << "Invalid activity level. Please enter a valid activity level: ";
        std::cin >> activityLevel;
    }
    std::cout << std::endl;
    // Set the activity level
    this->activityLevel = activityLevel;
}

/*
    Display the details of the person
*/
void Person::displayPerson() const
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    if (gender == "M")
        std::cout << "Gender : Male" << std::endl;
    else if (gender == "F")
        std::cout << "Gender: Female" << std::endl;
    std::cout << "Weight: " << std::fixed << std::setprecision(1) << weight << "kg" << std::endl;
    std::cout << "Height: " << std::fixed << std::setprecision(2) << height << "m" << std::endl;
    std::cout << "BMI: " << std::fixed << std::setprecision(2) << calculateBMI() << std::endl;
}