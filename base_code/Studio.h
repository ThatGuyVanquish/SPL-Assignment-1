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
    Studio(const Studio& StudioOther); //copy constructor
    Studio operator=(const Studio& StudioOther); // copy assignment
    Studio(const Studio&& StudioOther); // move constructor
    Studio operator=(const Studio&& StudioOther); // move assignment
    Studio(const std::string &configFilePath);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();
private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
    std::vector<std::string>* SplitSentence(const std::string &Sentence, char splt ); // helper method to phrase the input
};

#endif