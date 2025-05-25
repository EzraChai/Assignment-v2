#ifndef GOAL_H
#define GOAL_H

#include "Person.h"
#include "Diet.h"
#include "Workout.h"
#include <string>

const int MAX_WORKOUTS = 10;
const int MAX_DIETS = 8;

class BodyMetric : public Person
{
private:
    std::string goalType;
    Workout workout[MAX_WORKOUTS];
    Diet diet[MAX_DIETS];

public:
    BodyMetric();
    BodyMetric(std::string, int, std::string, double, double, std::string);
    ~BodyMetric();

    void createBodyMetric(std::string);
    std::string getGoalType() const;

    void estimateCaloriesIntake();

    void displayProfileInfo() const;

    void loadWorkoutsAndDietPlans();

    void generateDailyMealsPlan();

    void generateWorkoutPlan() const;

    bool isBurnValidForGender(int) const;
    bool isValidDailyCalories(int) const;

    void workoutCalculation() const;
    void dietCalculation();

    void updateProfile();
};

#endif