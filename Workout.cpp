#include "Workout.h"

#include <iostream>
#include <iomanip>
#include <string>

Workout::Workout() : workoutType(""), intensity(0),caloriesBurnedPerMinute(0) {}
Workout::Workout(std::string wt, int i, int c) : workoutType(wt), intensity(i), caloriesBurnedPerMinute(c) {}
void Workout::displayWorkout(int index) const
{
    std::cout << std::setw(20) << "Workout " << (index+1) << std::setw(20) << workoutType << std::setw(20) << intensity << std::setw(20) << caloriesBurnedPerMinute << std::endl;
}

std::string Workout::getWorkoutType() const
{
    return workoutType;
}
int Workout::getCaloriesBurnedPerMinute() const
{
    return caloriesBurnedPerMinute;
}