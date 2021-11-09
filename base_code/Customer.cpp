#include "Customer.h"
#include <algorithm>>
using namespace std;

// Concstructor
Customer::Customer(std::string c_name, int c_id):
    name(c_name),
    id(c_id)
    {};

std::string Customer::getName() const 
{
    return name;
}

int Customer::getId() const 
{
    return id;
}

// Sweaty Customer Constructor
SweatyCustomer::SweatyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
    {};

std::vector<int> SweatyCustomer::order(const std::vector<Workout>& workoutOptions)
{
    std:vector<int> wrk;
    for (Workout workout : workoutOptions)
    {
        if (workout.getType() == CARDIO)
        {
            wrk.push_back(workout.getId());
        }
    }
    return wrk;
}

// Cheap Customer Constructor
CheapCustomer::CheapCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

std::vector<int> CheapCustomer::order(const std::vector<Workout>& workoutOptions)
{
    int minPrice(workoutOptions[0].getPrice());
    int minId = 0;
    for (Workout wrk : workoutOptions)
    {
        if (wrk.getPrice() < minPrice)
        {
            minPrice = wrk.getPrice();
            minId = wrk.getId();
        }
    }
    return vector<int>(minId);
}

// Heavy Muscle Customer Constructor
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout>& workoutOptions)
{
    std::vector<int> wrk;
    std::vector<Workout> wrkCOpy(workoutOptions);
    std::sort(wrkCOpy.begin(), wrkCOpy.end(), compareAnae);
    for (Workout workout : wrkCOpy)
    {
        if (workout.getType() == ANAEROBIC)
        {
            wrk.push_back(workout.getId());
        }
    }
    return wrk;
}

bool compareAnae(Workout w1, Workout w2)
{
    if (w1.getType() == ANAEROBIC)
    {
        if (w2.getType() != ANAEROBIC)
            return false;
        else
        {
            return w1.getPrice() < w2.getPrice();
        }
    }
    else if (w2.getType() == ANAEROBIC)
    {
        return true;
    }
    return false;;
}

// Full Body Customer Constructor
FullBodyCustomer::FullBodyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

std::vector<int> FullBodyCustomer::order(const std::vector<Workout>& workoutOptions)
{
    int anaeId = -1;
    int anaeMin;
    int cardioId = -1;
    int cardioMin;
    int mixId = -1;
    int mixMax;
    for (Workout workout : workoutOptions)
    {
        if (workout.getType() == ANAEROBIC)
        {
            if (anaeId == -1)
            {
                anaeMin = workout.getPrice();
                anaeId = workout.getId();
            }
            else if (anaeMin > workout.getPrice())
            {
                anaeMin = workout.getPrice();
                anaeId = workout.getId();
            }            
        }
        else if(workout.getType() == CARDIO)
        {
            if (cardioId == -1)
            {
                cardioMin = workout.getPrice();
                cardioId = workout.getId();
            }
            else if (cardioMin > workout.getPrice())
            {
                cardioMin = workout.getPrice();
                cardioId = workout.getId();
            }            
        }
        else
        {
            if (mixId == -1)
            {
                mixMax = workout.getPrice();
                mixId = workout.getId();
            }
            else if (mixMax < workout.getPrice())
            {
                mixMax = workout.getPrice();
                mixId = workout.getId();
            }
        }
    }
    std::vector<int> ret = {cardioId, mixId, anaeId};
    return ret;
}