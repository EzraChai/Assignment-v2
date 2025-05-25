#include "Workout.h"

#include <iostream>
#include <iomanip>
#include <string>

/*
    Default constructor
*/
Workout::Workout() : workoutType(""), intensity(0), caloriesBurnedPerMinute(0) {}
/*
    Overloading constructor
*/
Workout::Workout(std::string wt, int i, int c) : workoutType(wt), intensity(i), caloriesBurnedPerMinute(c) {}

/*
    Destructor
*/
Workout::~Workout() {}

/*
    Display workout type based on the index in the workout plans
*/
void Workout::displayWorkout(int index) const
{
    std::cout << std::setw(8) << (index + 1) << std::setw(20) << workoutType << std::setw(20) << intensity << std::setw(20) << caloriesBurnedPerMinute << std::endl;
}
/*
    Get the workout type
*/
std::string Workout::getWorkoutType() const
{
    return workoutType;
}
/*
    Get the calories burned per minute
*/
int Workout::getCaloriesBurnedPerMinute() const
{
    return caloriesBurnedPerMinute;
}