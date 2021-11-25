#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"


class Studio{		
public:
	Studio();
    ~Studio();
    Studio(const Studio& StudioOther); // Copy constructor
    Studio& operator=(const Studio& StudioOther); // Copy assignment
    Studio(const Studio&& StudioOther); // Move constructor
    Studio& operator=(const Studio&& StudioOther); // Move assignment
    Studio(const std::string &configFilePath); // Constructor with filepath
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the actions history log
    std::vector<Workout>& getWorkoutOptions();
    bool canOpen(int tid, int numOfCustomers); // Checks if trainer can be opened
private:
    bool open;
    int _cid;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    std::vector<std::string>* SplitSentence(const std::string &Sentence, char splt ); /* Method to parse input. 
       Honestly I don't know why we made this, we could've and probably should've used stringstream or getline but 
       for some reason my friend couldn't figure out issues with getline so he made his own method. 
       We decided to keep it and made sure it doesn't leak.*/ 
};

#endif