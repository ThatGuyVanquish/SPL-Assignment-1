#include "Studio.h"
#include <iostream>
//using namespace std;
Studio::Studio(){

}
Studio::Studio(const std::string &configFilePath){  
    int data_type = 0; 
    int workout_id =0;
    std::string workout_name("");
    WorkoutType workout;
    std::string workoutTypeStr;
    int workout_price;  
    std::vector<std::string>* text_by_lines = SplitSentence(configFilePath,'\n');   
    std::vector<std::string>* WordsFromCase_;
    
    for (int j = 0; j < text_by_lines->size(); j++)
    {
      if((*text_by_lines)[j][0]='#'){
       j=j+1; 
       data_type+=1; //1 is num of trainers, 2 is capcitiys, 3 is workout types.  
      }
      if(data_type==2){
          for(int i = 0;i<(*text_by_lines)[j].size();i++){ //Checking which charcaters are numbers.
            char c = (*text_by_lines)[j][i];
            int currnum = c - '0';
            if(currnum>=0 and currnum<=9)//Currnum is indeed a number
            { 
             trainers.push_back(new Trainer (currnum)); // creating new, potential memory leaks
            }    
          }         
      }
      if(data_type==3){
        WordsFromCase_ = SplitSentence((*text_by_lines)[j],',');  
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
       
          workout_options.push_back(Workout(workout_id,workout_name,workout_price,workout));
          workout_id++;
          delete WordsFromCase_;
      }      
    }
    delete text_by_lines;
}
int Studio::getNumOfTrainers() const{
  return  trainers.size();
  
}
Trainer* Studio::getTrainer(int tid){
        return  trainers[tid];

    }
const std::vector<BaseAction*>& Studio::getActionsLog() const{

    } // Return a reference to the history of actions  	
std::vector<Workout>& Studio::getWorkoutOptions(){
    return  workout_options;
    }    


void Studio :: start(){
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
         line = "";
         }
         return text_by_lines;
    }
}
Studio::Studio(const Studio &StudioOther){

}
Studio Studio::operator=(const Studio &StudioOther){

}

