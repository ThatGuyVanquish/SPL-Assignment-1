#include "../include/Action.h"
#include "../include/Trainer.h"
#include "../include/Studio.h"

using namespace std;

extern Studio *backup;

BaseAction::BaseAction()
{};

BaseAction::~BaseAction(){}

ActionStatus BaseAction::getStatus() const
{
    return status;
}

void BaseAction::setStatus() {
    status = COMPLETED;
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
    calledAction = action;
}

void BaseAction::complete()
{
    status = COMPLETED;
}

void BaseAction::error(std::string err)
{
    status = ERROR;
    errorMsg = err;
    cout << errorMsg << endl;
}

std::string BaseAction::getErrorMsg() const
{
    return errorMsg;
}

OpenTrainer::OpenTrainer(int _id, std::vector<Customer *> &customersList) : 
BaseAction(),
trainerId(_id),
customers(customersList)
{};

OpenTrainer::~OpenTrainer(){}

std::vector<Customer*> OpenTrainer::getCustomers()
{
    return customers;
}

void OpenTrainer::act(Studio &studio)
{
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr or trainer->isOpen())
    {
        error("Workout session does not exist or is already open.");
    }
    else
    {
        trainer->openTrainer();
        for (Customer *customer : customers)
        {
            trainer->addCustomer(customer);
        }
        complete();
    }
}

std::string OpenTrainer::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

OpenTrainer *OpenTrainer::clone()
{
    return new OpenTrainer(*this);
}

Order::Order(int id): 
trainerId(id)
{};

Order::~Order(){};

void Order::act(Studio &studio)
{
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr or not trainer->isOpen())
    {
        error("Trainer does not exist or is not open");
    }
    else
    {
        for (Customer *customer : trainer->getCustomers())
        {
            if (customer->orderStatus())
            {
                continue;
            }
            std::vector<int> workouts = customer->order(studio.getWorkoutOptions());
            if (workouts.size() == 0)
            {
                trainer->removeCustomer(customer->getId());
                continue;
            }
            trainer->order(customer->getId(), workouts, studio.getWorkoutOptions());
            for (int i : workouts)
            {
                cout << customer->getName() + " is doing " + studio.getWorkoutOptions()[i].getName() << endl;
            }
        }
        complete();
    }
}

std::string Order::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

Order *Order::clone()
{
    return new Order(*this);
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId) : 
srcTrainer(src),
dstTrainer(dst),
id(customerId)
{};

MoveCustomer::~MoveCustomer(){}

void MoveCustomer::act(Studio &studio)
{
    Trainer *currTrainer = studio.getTrainer(srcTrainer);
    Trainer *nextTrainer = studio.getTrainer(dstTrainer);
    if (currTrainer != nullptr and currTrainer->isOpen() and                  // Source trainer exists and is open
        nextTrainer != nullptr and nextTrainer->isOpen() and                  // Destination trainer exists and is open
        (static_cast<int>(nextTrainer->getCustomers().size())) < nextTrainer->getCapacity() and // Destination has room for customers
        currTrainer->getCustomer(id) != nullptr)                              // Customer exists in source trainer's list
    {
        std::vector<Workout> workout_options = studio.getWorkoutOptions();
        Customer *currentCustomer = (currTrainer->getCustomer(id))->clone();
        std::vector<int> workouts = (currentCustomer->order(workout_options));
        if (currentCustomer->orderStatus())
        {
            nextTrainer->order(id, workouts, workout_options);
        }
        nextTrainer->addCustomer(currentCustomer);
        currTrainer->removeCustomerWithSalary(id);
        complete();
        if (currTrainer->getCustomers().empty())
        {
            currTrainer->closeTrainer();
        }
    }
    else
    {
        error("Cannot move customer");
    }
}

std::string MoveCustomer::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

MoveCustomer *MoveCustomer::clone()
{
    return new MoveCustomer(*this);
}

Close::Close(int id): 
trainerId(id)
{};

Close::~Close(){}

void Close::act(Studio &studio)
{
    vector<Customer*> temp;
    Trainer *trainer = studio.getTrainer(trainerId);
    temp = trainer->getCustomers();
    if (trainer == nullptr or not trainer->isOpen())
    {
        error("Trainer does not exist or is not open");
    }
    else
    {
        for (Customer* customer : temp)
        {
            trainer->removeCustomer(customer->getId());
        }
    trainer->closeTrainer();
    int tsal = trainer->getSalary();
    cout << "Trainer " + std::to_string(trainerId) + " closed. Salary " + std::to_string(tsal) + "NIS" << endl;
    complete();
   }
}

std::string Close::toString() const
{
    std::string ret;
        if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

Close *Close::clone()
{
    return new Close(*this);
}

CloseAll::CloseAll(){};

CloseAll::~CloseAll(){}

void CloseAll::act(Studio &studio)
{
    for (int i = 0; i < studio.getNumOfTrainers(); i++)
    {
        Trainer *currTrain = studio.getTrainer(i);
        if (currTrain->isOpen())
        {
            cout << "Trainer " << i << " closed."<< " Salary " << std::to_string(currTrain->getSalary()) << "NIS" << endl;
        }
    }
    complete();
}

std::string CloseAll::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

CloseAll *CloseAll::clone()
{
    return new CloseAll(*this);
}

PrintWorkoutOptions::PrintWorkoutOptions(){};

PrintWorkoutOptions::~PrintWorkoutOptions(){}

void PrintWorkoutOptions::act(Studio &studio)
{
    std::vector<Workout> wOptions = studio.getWorkoutOptions();
    for (Workout wrk : wOptions)
    {
        std::string type;
        switch (wrk.getType())
        {
        case ANAEROBIC:
        {
            type = "Anaerobic";
        }
        case CARDIO:
        {
            type = "Cardio";
        }
        case MIXED:
        {
            type = "Mixed";
        }
        }
        cout << wrk.getName() + ", " + type + ", " + std::to_string(wrk.getPrice()) << endl;
    }
    complete();
}

std::string PrintWorkoutOptions::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

PrintWorkoutOptions *PrintWorkoutOptions::clone()
{
    return new PrintWorkoutOptions(*this);
}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id){};

PrintTrainerStatus::~PrintTrainerStatus(){}

void PrintTrainerStatus::act(Studio &studio)
{
    Trainer *trainer = studio.getTrainer(trainerId);
    cout << "Trainer " + std::to_string(trainerId) + " status: " + trainer->getStatus() << endl;
    if (trainer->getStatus() == "open")
    { 
        cout << "Customers: " << endl;
        for (Customer *customer : trainer->getCustomers())
        {
            cout << std::to_string(customer->getId()) + " " + customer->getName() << endl;
        }
        cout << "Orders: " << endl;
        for (OrderPair order : trainer->getOrders())
        {
            cout << order.second.getName() + " " + std::to_string(order.second.getPrice()) + "NIS " + std::to_string(order.first) << endl;
        }
        cout << "Current Trainer's Salary: " + std::to_string(trainer->getSalary()) + "NIS" << endl;
    }
    complete();
}

std::string PrintTrainerStatus::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

PrintTrainerStatus *PrintTrainerStatus::clone()
{
    return new PrintTrainerStatus(*this);
}

PrintActionsLog::PrintActionsLog(){};

PrintActionsLog::~PrintActionsLog(){}

void PrintActionsLog::act(Studio &studio)
{
    for (BaseAction *action : studio.getActionsLog())
    {
        cout << action->getCalledAction() + " " + action->toString() << endl;
    }
    complete();
}

std::string PrintActionsLog::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

PrintActionsLog *PrintActionsLog::clone()
{
    return new PrintActionsLog(*this);
}

BackupStudio::BackupStudio(){};

BackupStudio::~BackupStudio(){}

void BackupStudio::act(Studio &studio)
{
    complete();
    delete backup;
    backup = new Studio(studio);
}

std::string BackupStudio::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

BackupStudio *BackupStudio::clone()
{
    return new BackupStudio(*this);
}

RestoreStudio::RestoreStudio(){};

RestoreStudio::~RestoreStudio(){}

void RestoreStudio::act(Studio &studio)
{
    if (backup != nullptr)
    {
        studio = *backup;
        complete();
    }
    else
    {
        error("No backup available");
    }
}

std::string RestoreStudio::toString() const
{
    std::string ret;
    if (getStatus() == COMPLETED)
    {
        ret = "Completed";
    }
    else 
    {
        ret = "Error " + getErrorMsg();
    }
    return ret;
}

RestoreStudio *RestoreStudio::clone()
{
    return new RestoreStudio(*this);
}