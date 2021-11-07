#include <string>
#include "Workout.h"

using namespace std;

Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):
    id(w_id), 
    name(w_name), 
    price(w_price), 
    type(w_type)
    {}; // Constructor
    
Workout::Workout(const Workout& w_existing):
    id(w_existing.getId()),
    name(w_existing.getName()),
    price(w_existing.getPrice()),
    type(w_existing.getType())
    {}; // Copy constructor

int Workout::getId() const {
    return id;
};

std::string Workout::getName() const{
    return name;
};

int Workout::getPrice() const{
    return price;
};
WorkoutType Workout::getType() const{
    return type;
};