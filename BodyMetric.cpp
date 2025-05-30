#include "BodyMetric.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

/*
    Default constructor
*/
BodyMetric::BodyMetric() : Person(), goalType("")
{
}

/*
    Overloading constructor
*/
BodyMetric::BodyMetric(std::string n, int a, std::string ge, double w, double h, std::string g) : Person(n, a, ge, w, h), goalType(g)
{
    loadWorkoutsAndDietPlans();
}

/*
    Destructor
*/
BodyMetric::~BodyMetric() {}

/*
    Create new record for body metric
*/
void BodyMetric::createBodyMetric(std::string name)
{
    std::cout << "Creating body metric for [" << name << "]" << std::endl;

    int age;
    std::cout << "Age: ";
    std::cin >> age;

    // Validate Age input
    while (age <= 0 || age > 120)
    {
        std::cout << "Invalid age. Please enter a valid age.";
        std::cout << "Age: ";
        std::cin >> age;
    }

    std::string gender;

    std::cout << "Gender (male/female): ";
    std::cin >> gender;

    // Validate gender input
    while (gender != "male" && gender != "female")
    {
        std::cout << "Invalid gender. Please enter only male or female.";
        std::cout << "Gender (male/female): ";
        std::cin >> gender;
    }

    double weight;
    std::cout << "Weight (kg): ";
    std::cin >> weight;

    // validate weight input
    while (weight <= 0)
    {
        std::cout << "Invalid weight. Please enter a valid weight.";
        std::cout << "Weight (kg): ";
        std::cin >> weight;
    }

    double height;
    std::cout << "Height (m): ";
    std::cin >> height;

    // validate height input
    while (height <= 0)
    {
        std::cout << "Invalid height. Please enter a valid height.";
        std::cout << "Height (m): ";
        std::cin >> height;
    }

    std::string goalType;
    std::cout << "Goal Type (lose, maintain, gain): ";
    std::cin >> goalType;

    // validate goal input
    while (goalType != "lose" && goalType != "maintain" && goalType != "gain")
    {
        std::cout << "Invalid goal type. Please enter only lose, maintain or gain.";
        std::cout << "Goal Type (lose, maintain, gain): ";
        std::cin >> goalType;
    }

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

/*
    Load workout and diet plans from external data
*/
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

/*
    Generate daily meal plans based on calories needed
*/
void BodyMetric::generateDailyMealsPlan()
{

    if (getActivityLevel() == 0)
    {
        promptUserForActivityLevel();
    }

    // Diets according their index
    int mealsIndex[MAX_DIETS] = {0, 4, 1, 5, 2, 6, 3, 7};

    // Find TDEE and adjust based on Goal Type
    double tdee = calculateTDEE();
    if (getGoalType() == "lose")
    {
        tdee -= 500;
    }
    else if (getGoalType() == "gain")
    {
        tdee += 500;
    }

    // If tdee <= 1450, then 3 meals is enough to generate
    int totalMeals = 4;
    if (tdee <= 1450)
    {
        totalMeals = 3;
    }

    // If tdee > 1700 and tdee < 2300, then 4 meals is enough to generate
    double totalTdeeLeft = tdee - 1700;
    if (totalTdeeLeft > 0)
    {
        totalMeals++;
        // If tdee > 2300, depending on the tdee, it add more meals accordingly
        while (totalTdeeLeft > 600)
        {
            totalTdeeLeft -= 600;
            totalMeals++;
        }
    }

    int generatedList[totalMeals] = {0};
    Diet totalDiet = Diet();
    // Adjust TDEE based on goal and gender since it cannot be less than 1200(female) or 1500(male)
    double minCalories = 0;
    if (getGender() == "M")
        minCalories = 1500;
    else if (getGender() == "F")
        minCalories = 1200;

    if (tdee < minCalories)
        tdee = minCalories;

    while (totalDiet.getCalories() < tdee)
    {
        // generate the meals randomly
        totalDiet = Diet();
        for (int i = 0; i < totalMeals; i++)
        {
            if (i < 4)
            {
                generatedList[i] = mealsIndex[rand() % 2 + (i * 2)];
                totalDiet = totalDiet + diet[generatedList[i]];
            }
            else
            {
                generatedList[i] = mealsIndex[rand() % MAX_DIETS];
                totalDiet = totalDiet + diet[generatedList[i]];
            }
        }
    }

    // To display meal plan generated
    std::cout << "------------ Daily Meal Plan ------------" << std::endl;
    std::cout << std::setw(20) << "Meal Type" << std::setw(30) << "Food" << std::setw(20) << "Calories" << std::endl;
    for (int i = 0; i < totalMeals; i++)
    {
        if (i == 4)
        {
            std::cout << std::setw(20) << "Additional meal: " << std::endl;
        }
        std::cout << std::setw(20) << diet[generatedList[i]].getMealType() << std::setw(30) << diet[generatedList[i]].getFood() << std::setw(20) << diet[generatedList[i]].getCalories() << std::endl;
    }
    std::cout << "Total calories: " << totalDiet.getCalories() << std::endl;
}

/*
    Display personal profile
*/
void BodyMetric::displayProfileInfo() const
{
    std::cout << "------------ Profile Information ------------" << std::endl;
    Person::displayPerson();
    std::cout << "Goal Type: " << goalType << std::endl;
    std::cout << std::endl;
}

/*
    Get Goal Type
*/
std::string BodyMetric::getGoalType() const
{
    return goalType;
}

/*
    Check if the total calories burned is valid based on the gender
*/
bool BodyMetric::isBurnValidForGender(int totalcaloriesBurned) const
{
    if (getGender() == "F")
    {
        return totalcaloriesBurned <= 400;
    }
    else if (getGender() == "M")
    {
        return totalcaloriesBurned <= 500;
    }
    return false;
}

/*
    Calculate workout calories burned
*/
void BodyMetric::workoutCalculation() const
{
    int workoutCount = 0;
    int totalCaloriesBurned = 0;

    std::cout << "------------ Workout Calculation ------------" << std::endl;
    std::cout << std::setw(8) << "Workout" << std::setw(20) << "Workout Type" << std::setw(20) << "Intensity" << std::setw(20) << "Calories Burned/Min" << std::endl;
    // Display all workouts
    for (int i = 0; i < MAX_WORKOUTS; i++)
    {
        workout[i].displayWorkout(i);
    }

    std::cout << "Enter the total number of workouts you did today: ";
    std::cin >> workoutCount;

    int workoutChoice[workoutCount];
    int workoutDuration[workoutCount];

    // input the workout indices
    std::cout << "Enter the workout indices (1 to " << MAX_WORKOUTS << "): " << std::endl;
    for (int i = 0; i < workoutCount; i++)
    {
        std::cin >> workoutChoice[i];
        // validate workout index input
        while (workoutChoice[i] <= 0 || workoutChoice[i] > 10)
        {
            std::cout << "Invalid workout index. Please enter valid workout index: ";
            std::cin >> workoutChoice[i];
        }
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

    if (isBurnValidForGender(totalCaloriesBurned))
    {
        std::cout << "Workout calories burned is within daily safe limit." << std::endl;
    }
    else
    {
        std::cout << "You have exceeded the recommended daily calorie burn which is " << ((getGender() == "M") ? "500" : "400") << " calories!" << std::endl;
        std::cout << std::endl;
    }
}

/*
    Check if the total calories consumed is valid based on the gender and BMR
*/
bool BodyMetric::isValidDailyCalories(int totalCalories) const
{
    double tdee = calculateTDEE();
    // Adjust TDEE based on goal and gender
    if (getGoalType() == "lose")
    {
        tdee -= 500;
    }
    else if (getGoalType() == "gain")
    {
        tdee += 500;
    }
    // Set minimum calories based on gender
    double minCalories = 0;
    if (getGender() == "M")
        minCalories = 1500;
    else if (getGender() == "F")
        minCalories = 1200;
    else
        return false; // Invalid gender

    if (tdee < minCalories)
        tdee = minCalories;

    return totalCalories >= tdee;

    return false;
}
/*
    Calculate diet calories consumed
    and check if it is valid based on the gender and BMR
*/
void BodyMetric::dietCalculation()
{

    int dietCount = 0;
    int totalCalories = 0;

    if (getActivityLevel() == 0)
    {
        promptUserForActivityLevel();
    }

    std::cout << "------------ Diet Calculation ------------" << std::endl;
    std::cout << std::setw(8) << "Meal" << std::setw(20) << "Meal Type" << std::setw(30) << "Food" << std::setw(20) << "Calories" << std::endl;
    // Display all diets
    for (int i = 0; i < MAX_DIETS; i++)
    {
        std::cout << std::setw(8) << (i + 1) << std::setw(20) << diet[i].getMealType() << std::setw(30) << diet[i].getFood() << std::setw(20) << diet[i].getCalories() << std::endl;
    }
    // Input the number of meals and validate the input
    std::cout << "Enter the total number of meals you had today: ";
    std::cin >> dietCount;
    while (dietCount < 0)
    {
        std::cout << "Invalid number of meals.\n Please enter a valid number of meals: ";
        std::cin >> dietCount;
    }

    // array to store the meal index
    int dietChoice[dietCount];

    // validate and input meal index
    std::cout << "Please enter the meal indexs (1 to " << MAX_DIETS << "): " << std::endl;
    for (int i = 0; i < dietCount; i++)
    {
        std::cin >> dietChoice[i];
        while (dietChoice[i] <= 0 || dietChoice[i] >= MAX_DIETS)
        {
            std::cout << "Invalid meal index. Please enter valid meal index.";
            std::cout << "Please enter the meal indexs (1 to " << MAX_DIETS << "): " << std::endl;
            std::cin >> dietChoice[i];
        }
    }
    // Diet summary and calculate the total calories consumed in a day
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

    double tdee = calculateTDEE();
    // Adjust TDEE based on goal and gender
    if (getGoalType() == "lose")
    {
        tdee -= 500;
    }
    else if (getGoalType() == "gain")
    {
        tdee += 500;
    }
    if (getGender() == "M" && tdee < 1500)
    {
        tdee = 1500;
    }
    else if (getGender() == "F" && tdee < 1200)
    {
        tdee = 1200;
    }

    // Give suggestion based on the total calories consumed
    if (!isValidDailyCalories(dietOfTheDay.getCalories()))
    {
        std::cout << "Calorie intake not within recommended limit.\n";

        if (getGender() == "F")
        {
            if (tdee > 1200)
            {
                if (totalCalories < tdee)
                    std::cout << "Suggestion: Add another snack.\n";
                else
                    std::cout << "Suggestion: Remove high-calorie item.\n";
            }
            else
            {
                if (totalCalories < 1200)
                    std::cout << "Suggestion: Add another snack.\n";
                else
                    std::cout << "Suggestion: Remove high-calorie item.\n";
            }
        }
        else
        {
            if (tdee > 1500)
            {
                if (totalCalories < tdee)
                    std::cout << "Suggestion: Add another snack.\n";
                else
                    std::cout << "Suggestion: Remove high-calorie item.\n";
            }
            else
            {
                if (totalCalories < 1500)
                    std::cout << "Suggestion: Add another snack.\n";
                else
                    std::cout << "Suggestion: Remove high-calorie item.\n";
            }
        }
    }
    else
    {
        std::cout << "Calorie intake is appropriate.\n";
    }
}

/*
    Update the profile information such as name, age, weight, height and goal
*/
void BodyMetric::updateProfile()
{
    int choice;

    while (choice != 6)
    {

        std::cout << "------------ Update Profile ------------" << std::endl;
        std::cout << "1. Name" << std::endl;
        std::cout << "2. Age" << std::endl;
        std::cout << "3. Weight" << std::endl;
        std::cout << "4. Height" << std::endl;
        std::cout << "5. Goal" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Select an option to update: ";
        std::cin >> choice;
        switch (choice)
        {
        //  Update name
        case 1:
        {
            std::string name;
            std::cout << "Current name: " << getName() << std::endl;
            std::cout << "Enter new name: ";
            std::cin >> name;
            setName(name);
            break;
        }
        //  Update age
        case 2:
        {
            int age;
            std::cout << "Current age: " << getAge() << std::endl;
            std::cout << "Enter new age: ";
            std::cin >> age;
            while (age <= 0 || age > 120)
            {
                std::cout << "Invalid age. Please enter a valid age.";
                std::cout << "Enter new age: ";
                std::cin >> age;
            }
            setAge(age);
            break;
        }
        //  Update weight
        case 3:
        {
            double weight;
            std::cout << "Current weight: " << getWeight() << std::endl;
            std::cout << "Enter new weight (kg): ";
            std::cin >> weight;
            while (weight <= 0)
            {
                std::cout << "Invalid weight. Please enter a valid weight.";
                std::cout << "Enter new weight (kg): ";
                std::cin >> weight;
            }
            setWeight(weight);
            break;
        }
        //  Update height
        case 4:
        {
            double height;
            std::cout << "Current height: " << getHeight() << std::endl;
            std::cout << "Enter new height (m): ";
            std::cin >> height;
            while (height <= 0)
            {
                std::cout << "Invalid height. Please enter a valid height.";
                std::cout << "Enter new height (m): ";
                std::cin >> height;
            }
            setHeight(height);
            break;
        }
        //  Update goal
        case 5:
        {
            std::string goal;
            std::cout << "Current goal: " << goalType << std::endl;
            std::cout << "Enter new goal (lose/maintain/gain): ";
            std::cin >> goal;
            while (goal != "lose" && goal != "maintain" && goal != "gain")
            {
                std::cout << "Invalid goal type. Please enter only lose, maintain or gain.";
                std::cout << "Enter new goal (lose/maintain/gain): ";
                std::cin >> goal;
            }
            goalType = goal;
            break;
        }
        case 6:
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        std::cout << "Profile updated successfully!\n"
                  << std::endl;
    }

    return;
}

/*
    Estimate calories intake based on BMR and TDEE
*/
void BodyMetric::estimateCaloriesIntake()
{
    // Show the goal and bmi of user
    std::cout << "------------ Estimate Calories Intake ------------" << std::endl;
    std::cout << "Your goal is: " << goalType << std::endl;
    std::cout << "Your BMI is: " << calculateBMI() << std::endl;
    std::cout << std::endl;
    // Determine daily activity level of user
    if (getActivityLevel() == 0)
    {
        promptUserForActivityLevel();
    }

    double tdee = calculateTDEE();

    // Adjust TDEE based on goal and gender
    if (getGoalType() == "lose")
    {
        tdee -= 500;
    }
    else if (getGoalType() == "gain")
    {
        tdee += 500;
    }
    if (getGender() == "M" && tdee < 1500)
    {
        tdee = 1500;
    }
    else if (getGender() == "F" && tdee < 1200)
    {
        tdee = 1200;
    }

    std::cout << "Your BMR is: " << calculateBMR() << " calories/day" << std::endl;
    std::cout << "Your daily calories intake is: " << tdee << " calories/day" << std::endl;
    std::cout << std::endl;
}

/*
    Generate workout plan by considering goal and gender
*/
void BodyMetric::generateWorkoutPlan() const
{
    /*
    Goal        Target Burn (Female)    Target Burn (Male)
    Lose        350–400 kcal            450–500 kcal
    Maintain    200–300 kcal            250–400 kcal
    Gain        ≤ 200 kcal              ≤ 250 kcal
    */

    // Display goal and bmi
    std::cout << "------------ Daily Workout Plan ------------" << std::endl;
    std::cout << "Your goal is: " << goalType << std::endl;
    std::cout << "Your BMI is: " << calculateBMI() << std::endl;

    // Array to store duration
    int duration[3] = {10, 20, 30};

    // Variable min and max target burn and workout num is initialized
    int maxTargetBurn = 0;
    int minTargetBurn = 0;
    int workoutNum = 0;

    // Adjust the min and maximum target burned and number of workout
    if (goalType == "lose")
    {
        if (getGender() == "F")
        {
            minTargetBurn = 350;
            maxTargetBurn = 400;
        }
        else if (getGender() == "M")
        {
            minTargetBurn = 450;
            maxTargetBurn = 500;
        }
        workoutNum = 3;
    }
    else if (goalType == "maintain")
    {
        if (getGender() == "F")
        {
            minTargetBurn = 200;
            maxTargetBurn = 300;
        }
        else if (getGender() == "M")
        {
            minTargetBurn = 250;
            maxTargetBurn = 400;
        }
        workoutNum = 2;
    }
    else if (goalType == "gain")
    {
        if (getGender() == "F")
        {
            minTargetBurn = 0;
            maxTargetBurn = 200;
        }
        else if (getGender() == "M")
        {
            minTargetBurn = 0;
            maxTargetBurn = 250;
        }
        workoutNum = 1;
    }

    int caloriesBurned = 0;

    // Dynamic allocate arrays to store workout index and corresponding duration
    int *ptrWorkoutIndex = new int[workoutNum];
    int *ptrWorkoutDuration = new int[workoutNum];
    std::cout << std::setw(20) << "Workout Type" << std::setw(20) << "Duration (min)" << std::setw(20) << "Calories Burned" << std::endl;

    // Generate random workout plan randomly until the total calories burned is within the target burn range
    while (!(caloriesBurned >= minTargetBurn && caloriesBurned <= maxTargetBurn))
    {
        caloriesBurned = 0;
        for (int i = 0; i < workoutNum; i++)
        {
            int workoutIndex = rand() % MAX_WORKOUTS;
            int durationIndex = rand() % 3;
            int caloriesBurnedValue = workout[workoutIndex].getCaloriesBurnedPerMinute() * duration[durationIndex];
            caloriesBurned += caloriesBurnedValue;
            ptrWorkoutIndex[i] = workoutIndex;
            ptrWorkoutDuration[i] = duration[durationIndex];
        }
    }
    // Display the workout plan
    for (int i = 0; i < workoutNum; i++)
    {
        int workoutIndex = ptrWorkoutIndex[i];
        int caloriesBurnedValue = workout[workoutIndex].getCaloriesBurnedPerMinute() * ptrWorkoutDuration[i];
        std::cout << std::setw(20) << workout[workoutIndex].getWorkoutType() << std::setw(20) << ptrWorkoutDuration[i] << std::setw(20) << caloriesBurnedValue << std::endl;
    }
    std::cout << "Total calories burned: " << caloriesBurned << std::endl;

    std::cout << std::endl;

    // Clear all the allocated memory
    delete[] ptrWorkoutIndex;
    delete[] ptrWorkoutDuration;
    ptrWorkoutIndex = nullptr;
    ptrWorkoutDuration = nullptr;
}