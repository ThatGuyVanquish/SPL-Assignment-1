#include "Studio.h"
#include <iostream>
#include <fstream>
using namespace std;
Studio::Studio(){} // Empty constructor
Studio::Studio(const std::string &configFilePath){  // Constructor with filepath
    string Text;
    ifstream MyReadFile(configFilePath);
    int data_type = 0; 
    std::string workout_name("");
    WorkoutType workout;
    std::string workoutTypeStr;
    std::vector<std::string>* WordsFromCase_;
    int workout_price;  
    int workoutId = 0;
    while (getline(MyReadFile,Text))
    {
        if (Text.empty())
        {
        continue;
        }
        if (Text[0] == '#')
      {
        data_type++;
      }
      else if (data_type == 2) 
      // 1 Is unnecessary because we can count number of different capacities
      {
        std::vector<std::string>* text_by_lines = SplitSentence(Text,',');
        for (std::string str : *text_by_lines)
        {
          trainers.push_back(new Trainer(stoi(str)));
        }
        delete text_by_lines;
      }
      else if (data_type == 3)
      {
        WordsFromCase_ = SplitSentence((Text),',');  
        workout_name = (*WordsFromCase_)[0];
        workoutTypeStr=(*WordsFromCase_)[1];
        if (workoutTypeStr == "Anaerobic")
        {
          workout = WorkoutType::ANAEROBIC;
        }
        if (workoutTypeStr == "Mixed")
        {
          workout = WorkoutType::MIXED;
        }
        if (workoutTypeStr == "Cardio")
        {
          workout = WorkoutType::CARDIO;
        }       
        workout_price =  stoi((*WordsFromCase_)[2]); // stoi function convert string to number.
        workout_options.push_back(Workout(workoutId,workout_name,workout_price,workout));
        workoutId++;
        delete WordsFromCase_;
      }
    }
    MyReadFile.close();
}

Studio::Studio(const Studio &StudioOther){ // probably like operator == but without deletion -Nave: is this our copy constructor?
    for (int i = 0; i < StudioOther.trainers.size(); i++)
    { 
      trainers.push_back(StudioOther.trainers[i]->clone());
    }
    for (int i = 0; i < StudioOther.actionsLog.size(); i++)
    {
     
      actionsLog.push_back(StudioOther.actionsLog[i]->clone());
    } 
     workout_options = StudioOther.workout_options;
}

Studio Studio::operator=(const Studio &StudioOther){ // Copy assignment
  if(this == &StudioOther)
  { //self assgiment
    return *this;
  }
  else
  {
     for (int i = 0; i < trainers.size(); i++)
    {
     
      delete trainers[i];
    }
    for (int i = 0; i < StudioOther.trainers.size(); i++)
    {
     
      trainers.push_back(StudioOther.trainers[i]);
    }
    for (int i = 0; i < actionsLog.size(); i++)
    {
     
      delete actionsLog[i];
    }
    for (int i = 0; i < StudioOther.actionsLog.size(); i++)
    {
     
      actionsLog.push_back(StudioOther.actionsLog[i]);
    } 
     workout_options = StudioOther.workout_options;
    
  }

}
Studio Studio::operator=(const Studio &&StudioOther){ //move assigment
    if (this == &StudioOther)
    {
      return *this;
    }
    for (int i = 0; i < trainers.size(); i++)
    {
      delete trainers[i];
    }
    for (int i = 0; i < StudioOther.trainers.size(); i++)
    {
      trainers.push_back(StudioOther.trainers[i]);
    }
    for (int i = 0; i < actionsLog.size(); i++)
    {
      delete actionsLog[i];
    }
    for (int i = 0; i < StudioOther.actionsLog.size(); i++)
    {
      actionsLog.push_back(StudioOther.actionsLog[i]);
    } 
     workout_options = StudioOther.workout_options;
    return *this;
}

Studio::~Studio() 
{
  for (Trainer* tr : trainers)
  {
      delete tr;
  }
  for (BaseAction* ba : actionsLog)
  {
    delete ba;
  }
  workout_options.clear(); // Might be useless
}


int Studio::getNumOfTrainers() const{
  return  trainers.size();
  
}
Trainer* Studio::getTrainer(int tid){
        if (tid < trainers.size())
        {
          return trainers[tid];
        }
        return nullptr;
    }

const std::vector<BaseAction*>& Studio::getActionsLog() const
{
    return actionsLog;
} // Return a reference to the history of actions  

std::vector<Workout>& Studio::getWorkoutOptions()
{
    return  workout_options;
}    

void Studio :: start()
{
    std::cout<<"The Studio is now open!"<<std::endl;
}

std::vector<std::string>* Studio::SplitSentence(const std::string &Sentence, char splt )
{
  std::string line("");
  std::vector<std::string>* text_by_lines = new std::vector<std::string>();   
    char current_char;
  for (int i = 0; i < Sentence.size(); i++)
    {
        current_char = Sentence[i];
        if (current_char != splt)
        {
          line.push_back(current_char);
        }
        else
        {
          text_by_lines->push_back(line);
          line="";
        }
    }
    return text_by_lines;
}

bool Studio::canOpen(int tid, int numOfCustomers)
{
    return (tid < trainers.size() && not trainers[tid]->isOpen() && trainers[tid]->getCapacity()-(trainers[tid]->getCustomers()).size() > numOfCustomers);
}