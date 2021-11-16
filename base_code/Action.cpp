#include "Action.h"
#include "Trainer.cpp"
#include "Studio.cpp"

BaseAction::BaseAction():
    errorMsg(nullptr),
    calledAction(nullptr)
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

void BaseAction::trigError(std::string err, std::string input)
{
    error(err);
    calledAction = input;
}

std::string BaseAction::getCalledAction()
{
    return calledAction;
}

void BaseAction::setCalledAction(std::string action)
{
    calledAction=action;
}

OpenTrainer::OpenTrainer(int _id, std::vector<Customer*> &customersList):
    BaseAction(),
    trainerId(_id),
    customers(customersList)
    {};

void OpenTrainer::act(Studio& studio)
{  
    Trainer* trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr or trainer->isOpen())
    {
        error("Workout session does not exist or is already open.");
    }
    else if (trainer->getCapacity()-(trainer->getCustomers()).size() < customers.size())
    {
        error("Trainer is in full capacity and can't hold the requested customer(s).");
    }
    else
    {
        trainer->openTrainer();
        for (Customer* customer : customers)
        {
            trainer->addCustomer(customer);
        }
        complete();
    }
}

std::string OpenTrainer::toString() const 
{
    // don't have to return anything really so:
    return "something";
}

OpenTrainer* OpenTrainer::clone() 
{
    return new OpenTrainer(*this);
}

Order::Order(int id):
trainerId(id)
{};

void Order::act(Studio& studio)
{
    Trainer* trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr or not trainer->isOpen())
    {
        error("Trainer does not exist or is not open");
    }
    else {
        for (Customer* customer : trainer -> getCustomers())
        {   
            std::vector<int> workouts = customer->order(studio.getWorkoutOptions());
            if (workouts.size() == 0)
            {
                trainer->removeCustomer(customer->getId());
                delete customer;
                continue;
            }
            trainer -> order(customer->getId(), workouts, studio.getWorkoutOptions());
            for (int i : workouts)
            {
                cout<<customer->getName() + " is doing " + studio.getWorkoutOptions()[i].getName()<< endl;
            }
        }
        complete(); // check if need to implement error checking
    }
}

std::string Order::toString() const
{
    return "hakuna matata";
}

Order* Order::clone() 
{
    return new Order(*this);
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
        std::vector<Workout> workout_options = studio.getWorkoutOptions();
        std::vector<int> workouts = (currTrainer->getCustomer(id))->order(workout_options);
        nextTrainer->order(id, workouts, workout_options);
        nextTrainer->addCustomer(currTrainer->getCustomer(id)->clone());
        currTrainer->removeCustomerWithSalary(id, true);
    }
    else
    {
        error("Cannot move customer");
    }
}

std::string MoveCustomer::toString() const
{
    return "";
}

MoveCustomer* MoveCustomer::clone() 
{
    return new MoveCustomer(*this);
}

Close::Close(int id): 
trainerId(id)
{};

void Close::act(Studio &studio)
{
    Trainer* trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr or not trainer->isOpen())
    {
        error("Can't close trainer because it does not exist or is already close.");
    }
    else
    {
        for (Customer* customer : trainer->getCustomers())
        {
            trainer->removeCustomer(customer->getId());
            delete customer;
        }
    }
    trainer->closeTrainer();
    // Might need to print "traine closed"
}

std::string Close::toString() const
{
    return "";
}

Close* Close::clone() 
{
    return new Close(*this);
}

CloseAll::CloseAll(){};

void CloseAll::act(Studio& studio)
{
    
}