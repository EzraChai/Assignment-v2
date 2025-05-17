#include <iostream>
#include <fstream>
#include <iomanip>
#include "BodyMetric.h"

int main(){
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
    if (userFile) {
        while (userFile >> name >> age >> gender >> weight >> height >> goal) {
            bodymetrics[personCount] = BodyMetric(name, age, gender, weight, height, goal); 
        }
        personCount++;
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
        counter++;
        bodymetrics[counter].createBodyMetric(name);
    }

    //TODO: Add a function to suggest a diet and workout plan based on the goal
    int userSelection = 0;
    while(userSelection != 5)
    {
        std::cout << "------------ Menu ------------" << std::endl;
        std::cout << "1. View Profile" << std::endl;
        std::cout << "2. Suggest a plan" << std::endl;
        std::cout << "3. Workout calculation" << std::endl;
        std::cout << "4. Diet ";
        std::cout << "4. Edit Profile" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> userSelection;

        switch(userSelection)
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
                bodymetrics[counter].createBodyMetric(name);
                std::cout << "Profile updated successfully!" << std::endl;
                break;
            case 5:
                break;
            default:
                std::cout << "Invalid selection, please try again." << std::endl;
        }
    }

    userFile.open("userInfo.txt", std::ios::out);
    if (userFile)
    {
        counter = 0;
        while(counter < personCount)
        {
            if(counter != 0)
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