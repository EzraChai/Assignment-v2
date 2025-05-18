#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "BodyMetric.h"

int main()
{
    srand(time(0)); // Seed for random number generation
    const int MAX_PERSONS = 50;
    BodyMetric bodymetrics[MAX_PERSONS];

    std::fstream userFile;
    userFile.open("userInfo.txt", std::ios::in);

    std::string name;
    int age;
    std::string gender;
    double weight;
    double height;
    std::string goal;

    int personCount = 0;
    if (userFile)
    {
        while (userFile >> name >> age >> gender >> weight >> height >> goal)
        {
            bodymetrics[personCount] = BodyMetric(name, age, gender, weight, height, goal);
            personCount++;
        }
        userFile.close();
    }
    std::cout << "------------ My Health Journey ------------" << std::endl;
    std::cout << "What is your name? ";
    std::cin >> name;

    int counter = 0;
    for (; counter < personCount; counter++)
    {
        if (bodymetrics[counter].getName() == name)
        {
            std::cout << "\nWelcome back, " << name << "!" << std::endl;
            break;
        }
    }
    if (personCount == counter && counter < MAX_PERSONS)
    {
        bodymetrics[counter].createBodyMetric(name);
        personCount++;
    }

    // TODO: Add a function to suggest a diet and workout plan based on the goal
    int userSelection = 0;
    while (userSelection != 7)
    {
        std::cout << "------------ Menu ------------" << std::endl;
        std::cout << "1. View Profile" << std::endl;
        std::cout << "2. Suggest a Plan" << std::endl;
        std::cout << "3. Workout Calculation" << std::endl;
        std::cout << "4. Generate Daily Meal Plan" << std::endl;
        std::cout << "5. Diet Calculation" << std::endl;
        std::cout << "6. Update Profile" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> userSelection;

        switch (userSelection)
        {
        case 1:
            bodymetrics[counter].displayProfileInfo();
            break;
        case 2:
            // bodymetrics[counter].suggestPlan();
            break;
        case 3:
            bodymetrics[counter].workoutCalculation();
            break;
        case 4:
            bodymetrics[counter].generateDailyMealsPlan();
            break;
        case 5:
            bodymetrics[counter].dietCalculation();
            break;
        case 6:
            bodymetrics[counter].updateProfile();
            break;
        case 7:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid selection, please try again." << std::endl;
        }
    }

    userFile.open("userInfo.txt", std::ios::out);
    if (userFile)
    {
        counter = 0;
        while (counter < personCount)
        {
            if (counter != 0)
            {
                userFile << '\n';
            }
            userFile << bodymetrics[counter].getName() << ' ';
            userFile << bodymetrics[counter].getAge() << ' ';
            userFile << bodymetrics[counter].getGender() << ' ';
            userFile << std::fixed << std::setprecision(1) << bodymetrics[counter].getWeight() << ' ';
            userFile << std::fixed << std::setprecision(2) << bodymetrics[counter].getHeight() << ' ';
            userFile << bodymetrics[counter].getGoalType();
            counter++;
        }
        userFile.close();
    }
}