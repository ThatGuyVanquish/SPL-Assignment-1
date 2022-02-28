#ifndef STUDIO_H_
#define STUDIO_H_

#include "Workout.h"
#include "Trainer.h"
#include "Action.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Studio{		
public:
    // Rule of Five
	Studio(); // Empty Constructor
    Studio(const std::string &configFilePath); // Constructor with filepath
    ~Studio(); // Deconstructor
    Studio(const Studio& StudioOther); // Copy constructor
    Studio& operator=(const Studio& StudioOther); // Copy assignment
    Studio(Studio&& StudioOther); // Move constructor
    Studio& operator=(Studio&& StudioOther); // Move assignment
    
    // Getters
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
    std::vector<Workout>& getWorkoutOptions();
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the actions history log
    
    // Actions
    void start();
    bool canOpen(int tid, int numOfCustomers); // Checks if trainer can be opened
    
private:
    bool open;
    int _cid;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    std::vector<std::string>* splitLine(const std::string &line, char delimeter); /* Method to parse input. 
       Honestly I don't know why we made this, we could've and probably should've used stringstream and getline but 
       for some reason Tom couldn't figure out issues with getline so he built his own version of it.
       We decided to keep it and made sure it doesn't leak.*/ 
};

#endif