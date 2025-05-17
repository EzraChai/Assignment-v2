#include "Person.h"
#include <string>
#include <iomanip>
#include <iostream>

// Default Contructor
Person::Person() : name(""), age(1), gender(""), weight(0.0), height(0.0) {}

Person::Person(std::string n, int a, std::string ge, double w, double h) : name(n), age(a), gender(ge), weight(w), height(h)
{
}

Person::~Person() {}

void Person::setName(std::string n)
{
    name = n;
}   
void Person::setAge(int a)
{
    age = a;
}
void Person::setGender(std::string ge){
    gender = ge;
}
void Person::setWeight(double w)
{
    weight = w;
}
void Person::setHeight(double h)
{
    height = h;
}


std::string Person::getName() const
{
    return name;
}
int Person::getAge() const
{
    return age;
}
std::string Person::getGender() const
{
    return gender;
}
double Person::getWeight() const
{
    return weight;
}
double Person::getHeight() const
{
    return height;
}

double Person::calculateBMI() const
{
    return (weight / (height * height));
}

void Person::displayPerson() const
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "Gender: " << gender << std::endl;
    std::cout << "Weight: " << std::fixed << std::setprecision(1) << weight << "kg" << std::endl;
    std::cout << "Height: " << std::fixed << std::setprecision(2) << height << "m" << std::endl;
    std::cout << "BMI: " << std::fixed << std::setprecision(2) << calculateBMI() << std::endl;
}