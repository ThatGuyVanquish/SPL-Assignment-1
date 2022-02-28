#include "../include/Customer.h"

Customer::Customer(std::string c_name, int c_id):
    name(c_name),
    id(c_id),
    hasOrdered(false)
    {};

Customer::~Customer(){}


// Getters

std::string Customer::getName() const 
{
    return name;
}

int Customer::getId() const 
{
    return id;
}

bool Customer::orderStatus() 
{
    return hasOrdered;
}


// Actions

void Customer::reqOrder()
{
    hasOrdered = true;
}

/*
**** Sweaty Customer ****
Order strategy:
Orders all of the available cardio workouts, by the order they've been received in the config file.
*/

SweatyCustomer::SweatyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
    {};

SweatyCustomer* SweatyCustomer::clone() 
{
    return new SweatyCustomer(getName(), getId());;
}

SweatyCustomer::~SweatyCustomer(){}


// Getters

std::string SweatyCustomer::toString() const
{
    return getId() + " " + getName();
}


// Actions

std::vector<int> SweatyCustomer::order(const std::vector<Workout>& workoutOptions)
{
    std::vector<int> workoutIds;
    for (Workout workout : workoutOptions)
    {
        if (workout.getType() == CARDIO)
            workoutIds.push_back(workout.getId());
    }
    reqOrder();
    return workoutIds;
}

/*
**** Cheap Customer ****
Order strategy:
Orders cheapest workout available.
*/

CheapCustomer::CheapCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

CheapCustomer* CheapCustomer::clone() 
{
    return new CheapCustomer(getName(), getId());;
}

CheapCustomer::~CheapCustomer(){}


// Getters

std::string CheapCustomer::toString() const
{
    return getId() + " " + getName();
}


// Actions

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
    reqOrder();
    return vector<int>({minId});
}


/*
**** Heavy Muscle Customer ****
Order strategy:
Anaerobic workouts from most expensive to cheapest.
*/

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

HeavyMuscleCustomer* HeavyMuscleCustomer::clone() 
{
    return new HeavyMuscleCustomer(getName(), getId());
}

HeavyMuscleCustomer::~HeavyMuscleCustomer(){}


// Getters

std::string HeavyMuscleCustomer::toString() const
{
    return getId() + " " + getName();
}


// Actions

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout>& workoutOptions)
{
    std::vector<int> wrk;
    std::vector<int> anaerobics;
    for (Workout wrk : workoutOptions)
    {
        if (wrk.getType() == ANAEROBIC)
            anaerobics.push_back(wrk.getPrice());
    }
    std::sort(anaerobics.begin(), anaerobics.end());
    std::vector<int> ids;
    for (int price : anaerobics)
    {
        for (Workout workout : workoutOptions)
        {
            if (workout.getPrice() == price and workout.getType() == ANAEROBIC)
            {
                if (std::find(ids.begin(), ids.end(), workout.getId()) == ids.end())
                    ids.push_back(workout.getId());
            }
        }
    }
    reqOrder();
    std::reverse(ids.begin(), ids.end());
    return ids;
}


/*
**** Full Body Customer ****
Order strategy:
1. Cheapest cardio
2. Most expensive mixed
3. Cheapest anaerobic
*/

FullBodyCustomer::FullBodyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

FullBodyCustomer* FullBodyCustomer::clone() 
{
    return new FullBodyCustomer(getName(), getId());;
}

FullBodyCustomer::~FullBodyCustomer(){}

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
    reqOrder();
    return ret;
}

std::string FullBodyCustomer::toString() const
{
    return getId() + " " + getName();
}