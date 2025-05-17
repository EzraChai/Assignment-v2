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

    void createBodyMetric(std::string);
    std::string getGoalType() const;
    // void suggestPlan();
    void displayProfileInfo() const;

    void loadWorkoutsAndDietPlans();

    void workoutCalculation() const;

    bool isBurnValidForGender(std::string, int) const;

    void dietCalculation() const;
};

#endif