#include "Person.h"
#include <string>
#include <iomanip>
#include <iostream>

/*
    Default constructor
*/
Person::Person() : name(""), age(1), gender(""), weight(0.0), height(0.0) {}

/*
    Overloading constructor
*/
Person::Person(std::string n, int a, std::string ge, double w, double h) : name(n), age(a), gender(ge), weight(w), height(h)
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
    age = a;
}

/*
    Set the gender the person
*/
void Person::setGender(std::string ge)
{
    gender = ge;
}

/*
    Set the weight of the person
*/
void Person::setWeight(double w)
{
    weight = w;
}

/*
    Set the height of the person
*/
void Person::setHeight(double h)
{
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
    Display the details of the person
*/
void Person::displayPerson() const
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Weight: " << std::fixed << std::setprecision(1) << weight << "kg" << std::endl;
    std::cout << "Height: " << std::fixed << std::setprecision(2) << height << "m" << std::endl;
    std::cout << "BMI: " << std::fixed << std::setprecision(2) << calculateBMI() << std::endl;
}