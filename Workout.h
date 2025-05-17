#ifndef WORKOUT_H
#define WORKOUT_H
#include <string>

class Workout
{
private:
    std::string workoutType;
    int intensity; // on a scale of 1 to 4
    int caloriesBurnedPerMinute;

public:
    Workout();
    Workout(std::string, int, int);

    void displayWorkout(int) const;
    std::string getWorkoutType() const; 
    int getCaloriesBurnedPerMinute() const;
};

#endif