#include "BodyMetric.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

BodyMetric::BodyMetric() : Person(), goalType("") {}
BodyMetric::BodyMetric(std::string n, int a, std::string ge, double w, double h, std::string g) : Person(n, a, ge, w, h), goalType(g)
{
    loadWorkoutsAndDietPlans();
}

void BodyMetric::createBodyMetric(std::string name)
{
    std::cout << "Creating body metric for [" << name << "]" << std::endl;

    int age;
    std::cout << "Age: ";
    std::cin >> age;

    std::string gender;
    std::cout << "Gender (male/female): ";
    std::cin >> gender;

    double weight;
    std::cout << "Weight (kg): ";
    std::cin >> weight;

    double height;
    std::cout << "Height (m): ";
    std::cin >> height;

    std::string goalType;
    std::cout << "Goal Type (lose, maintain, gain): ";
    std::cin >> goalType;

    // Set the values in the Person class
    this->setName(name);
    this->setAge(age);
    if (gender == "male")
    {
        this->setGender("M");
    }
    else if (gender == "female")
    {
        this->setGender("F");
    }
    this->setWeight(weight);
    this->setHeight(height);
    this->goalType = goalType;

    loadWorkoutsAndDietPlans();
}

void BodyMetric::loadWorkoutsAndDietPlans()
{
    std::ifstream workoutFile("workout_plans.txt");
    std::ifstream dietFile("diet_plans.txt");
    if (workoutFile)
    {
        int i = 0;

        // Read workout data from the file separated by ','
        while (i < MAX_WORKOUTS && workoutFile)
        {
            std::string workoutType;
            std::string intensity;
            std::string caloriesBurnedPerMinute;
            std::getline(workoutFile, workoutType, ',');
            std::getline(workoutFile, intensity, ',');
            std::getline(workoutFile, caloriesBurnedPerMinute);
            workout[i] = Workout(workoutType, std::stoi(intensity), std::stoi(caloriesBurnedPerMinute));
            i++;
        }
        workoutFile.close();
    }

    if (dietFile)
    {
        int i = 0;

        // Read diet data from the file
        while (i < MAX_DIETS && dietFile)
        {
            std::string mealType;
            std::string food;
            std::string calories;
            std::getline(dietFile, mealType, ',');
            std::getline(dietFile, food, ',');
            std::getline(dietFile, calories);
            diet[i] = Diet(mealType, food, std::stoi(calories));
            i++;
        }
        dietFile.close();
    }
}
void BodyMetric::generateDailyMealsPlan() const
{
    int breakfastIndex[2] = {0, 4};
    int lunchIndex[2] = {1, 5};
    int dinnerIndex[2] = {2, 6};
    int snackIndex[2] = {3, 7};

    int generatedList[4] = {0};
    Diet totalDiet = Diet();
    // do
    // {
    //     totalDiet = Diet();
    //     generatedList[0] = breakfastIndex[rand() % 2];
    //     totalDiet = totalDiet + diet[generatedList[0]];
    //     generatedList[1] = lunchIndex[rand() % 2];
    //     totalDiet = totalDiet + diet[generatedList[1]];
    //     generatedList[2] = dinnerIndex[rand() % 2];
    //     totalDiet = totalDiet + diet[generatedList[2]];
    //     generatedList[3] = snackIndex[rand() % 2];
    //     totalDiet = totalDiet + diet[generatedList[3]];
    // } while ((getGender() == "M" && totalDiet.getCalories() < 1500) ||
    //          (getGender() == "F" && totalDiet.getCalories() < 1200));

    std::cout << getGender() << std::endl;
    std::cout << totalDiet.getCalories() << std::endl;
    while ((getGender() == "M" && totalDiet.getCalories() < 1500) ||
           (getGender() == "F" && totalDiet.getCalories() < 1200))
    {
        totalDiet = Diet();
        generatedList[0] = breakfastIndex[rand() % 2];
        totalDiet = totalDiet + diet[generatedList[0]];
        generatedList[1] = lunchIndex[rand() % 2];
        totalDiet = totalDiet + diet[generatedList[1]];
        generatedList[2] = dinnerIndex[rand() % 2];
        totalDiet = totalDiet + diet[generatedList[2]];
        generatedList[3] = snackIndex[rand() % 2];
        totalDiet = totalDiet + diet[generatedList[3]];
    }

    std::cout << "------------ Daily Meal Plan ------------" << std::endl;
    std::cout << std::setw(20) << "Meal Type" << std::setw(30) << "Food" << std::setw(20) << "Calories" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << std::setw(20) << diet[generatedList[i]].getMealType() << std::setw(30) << diet[generatedList[i]].getFood() << std::setw(20) << diet[generatedList[i]].getCalories() << std::endl;
    }
    std::cout << "Total calories: " << totalDiet.getCalories() << std::endl;
}

void BodyMetric::displayProfileInfo() const
{
    std::cout << "------------ Profile Information ------------" << std::endl;
    Person::displayPerson();
    std::cout << "Goal Type: " << goalType << std::endl;
}

std::string BodyMetric::getGoalType() const
{
    return goalType;
}

bool BodyMetric::isBurnValidForGender(std::string gender, int totalcaloriesBurned) const
{
    if (gender == "F")
    {
        return totalcaloriesBurned <= 400;
    }
    else if (gender == "M")
    {
        return totalcaloriesBurned <= 500;
    }
    return false;
}

void BodyMetric::workoutCalculation() const
{
    int workoutCount = 0;
    int totalCaloriesBurned = 0;

    std::cout << "------------ Workout Calculation ------------" << std::endl;
    std::cout << std::setw(20) << "Workout index" << std::setw(20) << "Workout Type" << std::setw(20) << "Intensity" << std::setw(20) << "Calories Burned/Min" << std::endl;
    // Display all workouts
    for (int i = 0; i < MAX_WORKOUTS; i++)
    {
        workout[i].displayWorkout(i);
    }
    std::cout << "Enter the total number of workouts you did today: ";
    std::cin >> workoutCount;

    int workoutChoice[workoutCount];
    int workoutDuration[workoutCount];

    std::cout << "Enter the workout indexs (1 to " << MAX_WORKOUTS << "): " << std::endl;
    for (int i = 0; i < workoutCount; i++)
    {
        std::cin >> workoutChoice[i];
    }
    std::cout << "Enter the duration of each workout in minutes: " << std::endl;
    for (int i = 0; i < workoutCount; i++)
    {
        std::cout << workout[workoutChoice[i] - 1].getWorkoutType() << ": ";
        std::cin >> workoutDuration[i];
    }
    std::cout << "\n\n------------ Workout Summary ------------" << std::endl;
    std::cout << std::setw(20) << "Workout Type" << std::setw(20) << "Duration (min)" << std::setw(20) << "Calories Burned" << std::endl;
    for (int i = 0; i < workoutCount; i++)
    {
        int workoutIndex = workoutChoice[i] - 1;
        int duration = workoutDuration[i];
        int caloriesBurned = workout[workoutIndex].getCaloriesBurnedPerMinute() * duration;
        totalCaloriesBurned += caloriesBurned;
        std::cout << std::setw(20) << workout[workoutIndex].getWorkoutType() << std::setw(20) << duration << std::setw(20) << caloriesBurned << std::endl;
    }

    std::cout << "Total Calories Burned in a day: " << totalCaloriesBurned << std::endl;

    if (isBurnValidForGender(getGender(), totalCaloriesBurned))
    {
        std::cout << "Workout calories burned is within daily safe limit." << std::endl;
    }
    else
    {
        std::cout << "You have exceeded the recommended daily calorie burn which is " << ((getGender() == "M") ? "500" : "400") << " calories!" << std::endl;
        std::cout << std::endl;
    }
}

bool BodyMetric::isValidDailyCalories(std::string gender, int totalCalories) const
{
    if (gender == "F")
        return totalCalories >= 1200;
    if (gender == "M")
        return totalCalories >= 1500;
    return false;
}

void BodyMetric::dietCalculation() const
{
    int dietCount = 0;
    int totalCalories = 0;

    std::cout << "------------ Diet Calculation ------------" << std::endl;
    std::cout << std::setw(20) << "Meal Type" << std::setw(30) << "Food" << std::setw(20) << "Calories" << std::endl;
    // Display all diets
    for (int i = 0; i < MAX_DIETS; i++)
    {
        std::cout << std::setw(20) << diet[i].getMealType() << std::setw(30) << diet[i].getFood() << std::setw(20) << diet[i].getCalories() << std::endl;
        // diet[i].displayDiet();
    }
    std::cout << "Enter the total number of meals you had today: ";
    std::cin >> dietCount;

    int dietChoice[dietCount];

    std::cout << "Enter the meal indexs (1 to " << MAX_DIETS << "): " << std::endl;
    for (int i = 0; i < dietCount; i++)
    {
        std::cin >> dietChoice[i];
    }
    std::cout << "\n\n------------ Diet Summary ------------" << std::endl;
    std::cout << std::setw(20) << "Meal Type" << std::setw(30) << "Food" << std::setw(20) << "Calories" << std::endl;
    Diet dietOfTheDay;
    for (int i = 0; i < dietCount; i++)
    {
        int dietIndex = dietChoice[i] - 1;
        dietOfTheDay = dietOfTheDay + diet[dietIndex];
        std::cout << std::setw(20) << diet[dietIndex].getMealType() << std::setw(30) << diet[dietIndex].getFood() << std::setw(20) << diet[dietIndex].getCalories() << std::endl;
    }
    std::cout << "Total calories consumed in a day: " << dietOfTheDay.getCalories() << std::endl;

    if (!isValidDailyCalories(getGender(), dietOfTheDay.getCalories()))
    {
        std::cout << "Calorie intake not within recommended limit for gender.\n";

        if (getGender() == "F")
        {
            if (totalCalories < 1200)
                std::cout << "Suggestion: Add another snack.\n";
            else
                std::cout << "Suggestion: Remove high-calorie item.\n";
        }
        else
        {
            if (totalCalories < 1500)
                std::cout << "Suggestion: Add a heavier lunch.\n";
            else
                std::cout << "Suggestion: Replace dinner with something lighter.\n";
        }
    }
    else
    {
        std::cout << "Calorie intake is appropriate for gender.\n";
    }
}