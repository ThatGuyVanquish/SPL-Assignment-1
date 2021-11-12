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

std::string BaseAction::getErrorMsg() const
{
    return errorMsg;
}

OpenTrainer::OpenTrainer(int _id, std::vector<Customer*> &customersList):
    BaseAction(),
    trainerId(_id),
    customers(customersList),
    isOpen(false)
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
        for (Customer* customer : customers)
        {
            trainer -> addCustomer(customer);
        }
    }
}

std::string OpenTrainer::toString() const 
{
    // std::string ret("Trainer " + trainerId); // no idea why this is broken
    // ret.append(" status: ");
    // if (isOpen)
    // {
    //     ret.append("open\n");
    //     std::string workouts;
    //     for (Customer* customer : customers)
    //     {
    //         ret.append("" + customer->getId() + customer->getName() + "\n");
    //         for (Workout workout : thisStudio.getWorkoutOptions())
    //         {
                
    //         }
    //     }
    // ret.append("Current Trainer's Salary: ");//UNIMPLEMENTED NEED A WAY TO RETURN SALARY
    // }
    // else 
    // {
    //     ret.append("closed\n");
    // }
    
    // return ret;
}

Order::Order(int id):
trainerId(id)
{};

void Order::act(Studio& studio)
{
    Trainer* trainer = studio.getTrainer(trainerId);
    for (Customer* customer : trainer -> getCustomers())
    {   
        std::vector<int> workouts = customer->order(studio.getWorkoutOptions());
        trainer -> order(customer->getId(), workouts, studio.getWorkoutOptions());
        for (int i : workouts)
        {
            cout<<customer->getName() + " is doing " + studio.getWorkoutOptions()[i].getName()<< endl;
        }
    }
    trainer -> calcSalary();
}

std::string Order::toString() const
{
    // no idea what to return here
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId):
    srcTrainer(src),
    dstTrainer(dst),
    id(customerId)
    {};

void MoveCustomer::act(Studio& studio)
{
    Trainer* currTrainer = studio.getTrainer(srcTrainer);
    Trainer* nextTrainer = studio.getTrainer(dstTrainer);
    if (currTrainer != nullptr and currTrainer->isOpen() and // Source trainer exists and is open
    nextTrainer != nullptr and nextTrainer->isOpen() and // Destination trainer exists and is open
    (nextTrainer->getCustomers()).size() < nextTrainer->getCapacity() and // Destination has room for customers
    currTrainer->getCustomer(id) != nullptr) // Customer exists in source trainer's list
    {
        /*
            We need to:
            A. Move the workouts that customer (id) has stored in souce trainer's
            orderList by OrderPairs to the destination trainer
            B. During this, $$$$ if we need to store an accumulative salary
            then create another function to calculate negation of removed
            activities, maybe do that anyways and comment it out for now
            then delete if unnecessary (and 0 salary each time calcSalary is called)
            or uncomment it if it is necessary.
            C. Move the customer to the destination trainer's customerList
            D. Calculate the destination trainer's salary
        */
    }
}