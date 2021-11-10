#include "Action.h"
#include "Trainer.cpp"
#include "Studio.cpp"

BaseAction::BaseAction():
    errorMsg(nullptr)
    {};

ActionStatus BaseAction::getStatus() const 
{
    return status;
}

void BaseAction::complete() 
{
    status = COMPLETED;
}

void BaseAction::error(std::string err) 
{
    status = ERROR;
    errorMsg = err;
    cout<<errorMsg<<endl;
}

OpenTrainer::OpenTrainer(int _id, std::vector<Customer*> &customersList):
    BaseAction(), // maybe useless
    trainerId(_id),
    customers(customersList),
    isOpen(false),
    thisStudio()
    {};

void OpenTrainer::act(Studio& studio)
{  
    Trainer* trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr || trainer -> isOpen())
    {
        error("Workout session does not exist or is already open.");
    }
    else
    {
        trainer -> openTrainer();
        isOpen = true;
        thisStudio = studio;
    }
}

std::string OpenTrainer::toString() const 
{
    std::string ret("Trainer " + trainerId); // no idea why this is broken
    ret.append(" status: ");
    if (isOpen)
    {
        ret.append("open\n");
        std::string workouts;
        for (Customer* customer : customers)
        {
            ret.append("" + customer->getId() + customer->getName() + "\n");
            for (Workout workout : thisStudio.getWorkoutOptions())
            {
                
            }
        }
    ret.append("Current Trainer's Salary: ");//UNIMPLEMENTED NEED A WAY TO RETURN SALARY
    }
    else 
    {
        ret.append("closed\n");
    }
    
    return ret;
}