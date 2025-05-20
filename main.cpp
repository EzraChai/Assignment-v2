#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "BodyMetric.h"

/*
    Function prototype of the friend function
*/
void displayComparisonBetweenPerson(const Person &person1, const Person &person2);

int main()
{
    // Seed for random number generation
    srand(time(0));
    // Constants of maximum persons are initialized
    const int MAX_PERSONS = 50;
    // Array of bodymetrics is declared
    BodyMetric bodymetrics[MAX_PERSONS];

    // Open the user information file for reading
    std::fstream userFile;
    userFile.open("userInfo.txt", std::ios::in);

    // Variables are declared
    std::string name;
    int age;
    std::string gender;
    double weight;
    double height;
    std::string goal;

    int personCount = 0;
    // Read the file and stored into the array
    if (userFile)
    {
        while (userFile >> name >> age >> gender >> weight >> height >> goal)
        {
            bodymetrics[personCount] = BodyMetric(name, age, gender, weight, height, goal);
            personCount++;
        }
        userFile.close();
    }
    else
    {
        // If the file cannot be opened, stop the program with error code.
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    std::cout << "------------ My Health Journey ------------" << std::endl;
    std::cout << "What is your name? ";
    std::cin >> name;

    int personIndex = 0;
    // Find user in the userinfo and prompt the user with welcoming message
    for (; personIndex < personCount; personIndex++)
    {
        if (bodymetrics[personIndex].getName() == name)
        {
            std::cout << "\nWelcome back, " << name << "!" << std::endl;
            break;
        }
    }
    // If user is not found, register the user and write it into userinfo file.
    if (personCount == personIndex && personIndex < MAX_PERSONS)
    {
        bodymetrics[personIndex].createBodyMetric(name);
        personCount++;
    }

    int userSelection = 0;
    // Display the main menu in a loop unitl the user exits
    while (userSelection != 9)
    {
        std::cout << "------------ Menu ------------" << std::endl;
        std::cout << "1. View Profile" << std::endl;
        std::cout << "2. Estimate Calories Intake " << std::endl;
        std::cout << "3. Generate Workout Plan" << std::endl;
        std::cout << "4. Workout Calculation" << std::endl;
        std::cout << "5. Generate Daily Meal Plan" << std::endl;
        std::cout << "6. Diet Calculation" << std::endl;
        std::cout << "7. Compare with Another Person" << std::endl;
        std::cout << "8. Update Profile" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Select an option: ";
        std::cin >> userSelection;

        std::string otherName;
        switch (userSelection)
        {
        case 1:
            // Display user profile
            bodymetrics[personIndex].displayProfileInfo();
            break;
        case 2:
            // Estimate calories intake by user
            bodymetrics[personIndex].estimateCaloriesIntake();
            break;
        case 3:
            // Generate workout plan based on the user needed
            bodymetrics[personIndex].generateWorkoutPlan();
            break;
        case 4:
            // Calculate the workout calories burned
            bodymetrics[personIndex].workoutCalculation();
            break;
        case 5:
            // Generate the daily meals plan based on the user needed
            bodymetrics[personIndex].generateDailyMealsPlan();
            break;
        case 6:
            // Calculate the diet calories consumed
            bodymetrics[personIndex].dietCalculation();
            break;
        case 7:
        {
            // Compare the body health with other user
            std::cout << "Enter the name of the person to compare with: ";
            std::cin >> otherName;
            // Prompt user with error message ifthe user enter himself/herself
            if (otherName == bodymetrics[personIndex].getName())
            {
                std::cout << "You cannot compare yourself." << std::endl;
                break;
            }

            int otherIndex = -1;
            for (int i = 0; i < personCount; i++)
            {
                if (bodymetrics[i].getName() == otherName)
                {
                    otherIndex = i;
                    break;
                }
            }

            // Prompt user if the person is not found
            if (otherIndex == -1)
            {
                std::cout << "Person not found!\n"
                          << std::endl;
                break;
            }
            displayComparisonBetweenPerson(bodymetrics[personIndex], bodymetrics[otherIndex]);
            break;
        }
        case 8:
            // Update the profile of the user if needed
            bodymetrics[personIndex].updateProfile();
            break;
        case 9:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid selection, please try again." << std::endl;
        }
    }
    userFile.open("userInfo.txt", std::ios::out);
    if (userFile)
    {
        personIndex = 0;
        while (personIndex < personCount)
        {
            if (personIndex != 0)
            {
                userFile << '\n';
            }
            userFile << bodymetrics[personIndex].getName() << ' ';
            userFile << bodymetrics[personIndex].getAge() << ' ';
            userFile << bodymetrics[personIndex].getGender() << ' ';
            userFile << std::fixed << std::setprecision(1) << bodymetrics[personIndex].getWeight() << ' ';
            userFile << std::fixed << std::setprecision(2) << bodymetrics[personIndex].getHeight() << ' ';
            userFile << bodymetrics[personIndex].getGoalType();
            personIndex++;
        }
        userFile.close();
    }
}

void displayComparisonBetweenPerson(const Person &person1, const Person &person2)
{
    std::cout << "\n--------------------- Health Comparison ---------------------" << std::endl;
    std::cout << std::setw(15) << "Parameter" << std::setw(15) << person1.name << std::setw(15) << person2.name << std::setw(15) << "Difference" << std::endl;

    // Compare weights
    double weightDiff = std::abs(person1.weight - person2.weight);
    std::cout << std::setw(15) << "Weight (kg)" << std::setw(15) << std::fixed << std::setprecision(1)
              << person1.weight << std::setw(15) << person2.weight
              << std::setw(15) << weightDiff << std::endl;

    // Compare heights
    double heightDiff = std::abs(person1.height - person2.height);
    std::cout << std::setw(15) << "Height (m)" << std::setw(15) << std::fixed << std::setprecision(2)
              << person1.height << std::setw(15) << person2.height
              << std::setw(15) << heightDiff << std::endl;

    // Compare BMI
    double bmi1 = person1.calculateBMI();
    double bmi2 = person2.calculateBMI();
    double bmiDiff = std::abs(bmi1 - bmi2);
    std::cout << std::setw(15) << "BMI" << std::setw(15) << std::fixed << std::setprecision(2)
              << bmi1 << std::setw(15) << bmi2
              << std::setw(15) << bmiDiff << std::endl;

    std::cout << std::endl;
}