#include "Studio.h"
#include <iostream>

Studio::Studio(){

}
Studio::Studio(const std::string &configFilePath){  
    int data_type = 0; 
    int workout_id =0;
    std::string workout_name("");
    WorkoutType workout;
    int workout_price;  
    std::string line("");
    std::vector<std::string> text_by_lines;   
    char current_char;                 //each cell will a field from the class
    
    for (int i = 0; i < configFilePath.size(); i++)
    {
        current_char = configFilePath[i];
        if (current_char != '\n')
        {
            line.push_back(current_char);            
        }
        else
        {
         text_by_lines.push_back(line);
         line = "";
         }
               
    }
    for (int j = 0; j < text_by_lines.size(); j++)
    {
      if(text_by_lines[j][0]='#'){
       j=j+1; 
       data_type+=1; //1 is num of trainers, 2 is capcitiys, 3 is workout types.  
      }
      if(data_type==2){
          for(int i = 0;i<text_by_lines[j].size();i++){ //Checking which charcaters are numbers.
            char c = text_by_lines[j][i];
            int currnum = c - '0';
            if(currnum>=0 and currnum<=9)//Currnum is indeed a number
            { 
             trainers.push_back(new Trainer (currnum)); // creating new, potential memory leaks
            }    
          }
          
      }
      if(data_type==3){
       WorkoutType[0]
          workout_options.push_back(Workout(workout_id,workout_name,workout_price,workout_type))
      }      
    }
    
}
int Studio::getNumOfTrainers() const{
  return  trainers.size();
  
}
Trainer* Studio::getTrainer(int tid){
        return  trainers[tid];

    }
  	const std::vector<BaseAction*>& Studio::getActionsLog() const{

    } // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions(){

    }


void Studio :: start(){
    std::cout<<"The Studio is now open!"<<std::endl;
}


