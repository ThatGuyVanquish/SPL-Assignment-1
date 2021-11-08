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
    BaseAction(),
    trainerId(_id),
    customers(customersList),
    isOpen(false)
    {};

void OpenTrainer::act(Studio& studio)
{
    // add check if trainer exists
    Trainer* trainer = studio.getTrainer(trainerId);
    if (trainer->isOpen())
    {
        error("Workout session does not exist or is already open.");
    }
    else
    {
        trainer->openTrainer();
    }
    isOpen = true;
}

std::string OpenTrainer::toString() const 
{
    std::string trainerStatus("closed");
    if (isOpen)
    {
        trainerStatus="open";
    }
    std::string ret("Trainer " + trainerId + " status: " + trainerStatus + "\nCustomers:\n");
    for (int i = 0; i <= customers.size(); i++)
    {
        ret.append("" + customers[i]->getId() + customers[i]->getName() + "\n");
    }
    ret.append("Current Trainer's Salary: ");//UNIMPLEMENTED NEED A WAY TO RETURN SALARY
    return ret;
}