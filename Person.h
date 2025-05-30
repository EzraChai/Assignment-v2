#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person
{
private:
    std::string name;
    int age;
    std::string gender;
    double weight;
    double height;
    int activityLevel;

public:
    Person();
    Person(std::string, int, std::string, double, double);
    ~Person();

    void setName(std::string);
    void setAge(int);
    void setGender(std::string);
    void setWeight(double);
    void setHeight(double);

    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    double getWeight() const;
    double getHeight() const;
    int getActivityLevel() const;

    double calculateBMI() const;
    void displayPerson() const;

    double calculateBMR() const;
    double calculateTDEE() const;
    void promptUserForActivityLevel();

    friend void displayComparisonBetweenPerson(const Person &, const Person &);
};

#endif