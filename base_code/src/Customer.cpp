#include "../include/Customer.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// Concstructor
Customer::Customer(std::string c_name, int c_id):
    name(c_name),
    id(c_id),
    hasOrdered(false)
    {};

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

void Customer::reqOrder()
{
    hasOrdered = true;
}

Customer::~Customer()
{
    cout<<"delcustomer"<<endl;
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

/*
**** Sweaty Customer ****
Order strategy:
Orders all of the available cardio workouts, by the order they've been received in the config file.
*/

// Constructor
SweatyCustomer::SweatyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
    {};

SweatyCustomer* SweatyCustomer::clone() 
{
    return new SweatyCustomer(getName(), getId());;
}

std::vector<int> SweatyCustomer::order(const std::vector<Workout>& workoutOptions)
{
    std::vector<int> wrk;
    for (Workout workout : workoutOptions)
    {
        if (workout.getType() == CARDIO)
        {
            wrk.push_back(workout.getId());
        }
    }
    reqOrder();
    return wrk;
}

std::string SweatyCustomer::toString() const
{
    return getId() + " " + getName();
}

SweatyCustomer::~SweatyCustomer()
{
    cout<<"sweatydel"<<endl;
}

/*
**** Cheap Customer ****
Order strategy:
Orders cheapest workout available.
*/

// Constructor
CheapCustomer::CheapCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

CheapCustomer* CheapCustomer::clone() 
{
    return new CheapCustomer(getName(), getId());;
}

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
    vector<int> orderList;
    orderList.push_back(minId);
    return orderList;
}

std::string CheapCustomer::toString() const
{
    return getId() + " " + getName();
}

CheapCustomer::~CheapCustomer()
{
    cout<<"cheapdel"<<endl;
}

/*
**** Heavy Muscle Customer ****
Order strategy:
Anaerobic workouts from most expensive to cheapest.
*/

//  Constructor
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

HeavyMuscleCustomer* HeavyMuscleCustomer::clone() 
{
    return new HeavyMuscleCustomer(getName(), getId());
}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout>& workoutOptions)
{
    std::vector<int> wrk;
    std::vector<int> anaerobics;
    int ifd = 0;
    for (Workout wrk : workoutOptions)
    {
        if (wrk.getType() == ANAEROBIC)
        {
            anaerobics.push_back(wrk.getPrice());
            ifd++;
        }
    }
    std::sort(anaerobics.begin(), anaerobics.end());
    std::vector<int> ids;
    for (int i = 0; i < anaerobics.size(); i++)
    {
        for (int j = 0; j < workoutOptions.size(); j++)
        {
            if (workoutOptions[j].getPrice() == anaerobics[i] and workoutOptions[j].getType() == ANAEROBIC)
            {
                ids.push_back(workoutOptions[j].getId());
                break;
            }
        }
    }
    reqOrder();
    std::reverse(ids.begin(), ids.end());
    return ids;
}

std::string HeavyMuscleCustomer::toString() const
{
    return getId() + " " + getName();
}

HeavyMuscleCustomer::~HeavyMuscleCustomer()
{
    cout<<"heavydel"<<endl;
}

/*
**** Full Body Customer ****
Order strategy:
1. Cheapest cardio
2. Most expensive mixed
3. Cheapest anaerobic
*/

// Constructor
FullBodyCustomer::FullBodyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

FullBodyCustomer* FullBodyCustomer::clone() 
{
    return new FullBodyCustomer(getName(), getId());;
}

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

FullBodyCustomer::~FullBodyCustomer()
{
    cout<<"fulldel"<<endl;
}
