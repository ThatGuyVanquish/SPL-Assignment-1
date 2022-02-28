#include "../include/Action.h"

extern Studio *backup;


// BaseAction class
BaseAction::BaseAction(){} // Constructor

BaseAction::~BaseAction(){} // Deconstructor

ActionStatus BaseAction::getStatus() const {return status;}

void BaseAction::setStatus() {status = COMPLETED;}

void BaseAction::trigError(std::string err, std::string input)
{
    error(err);
    calledAction = input;
}

std::string BaseAction::getCalledAction() {return calledAction;}

void BaseAction::setCalledAction(std::string action) {calledAction = action;}

void BaseAction::complete() {status = COMPLETED;}

void BaseAction::error(std::string err)
{
    status = ERROR;
    errorMsg = err;
    cout << errorMsg << endl;
}

std::string BaseAction::getErrorMsg() const {return errorMsg;}


// OpenTrainer Class
OpenTrainer::OpenTrainer(int _id, std::vector<Customer *> &customersList) : // Constructor
BaseAction(),
trainerId(_id),
customers(customersList)
{};

OpenTrainer *OpenTrainer::clone() {return new OpenTrainer(*this);}

OpenTrainer::~OpenTrainer() {customers.clear();} // Deconstructor

std::vector<Customer*> OpenTrainer::getCustomers()
{
    return customers;
}

// Getters
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

// Actions
void OpenTrainer::act(Studio &studio)
{
    Trainer *trainer = studio.getTrainer(trainerId);
    if (trainer == nullptr or trainer->isOpen())
    {
        error("Trainer does not exist or is already open.");
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

// Order Class
Order::Order(int id): // Constructor
trainerId(id)
{}

Order *Order::clone() {return new Order(*this);}

Order::~Order(){} // Deconstructor

// Getters
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

// Actions
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


// MoveCustomer Class
MoveCustomer::MoveCustomer(int src, int dst, int customerId) : // Constructor
srcTrainer(src),
dstTrainer(dst),
id(customerId)
{};

MoveCustomer *MoveCustomer::clone() {return new MoveCustomer(*this);}

MoveCustomer::~MoveCustomer(){} // Deconstructor

// Getters
std::string MoveCustomer::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
void MoveCustomer::act(Studio &studio)
{
    Trainer *currTrainer = studio.getTrainer(srcTrainer);
    Trainer *nextTrainer = studio.getTrainer(dstTrainer);
    if (currTrainer != nullptr && currTrainer->isOpen() &&                  // Source trainer exists and is open
        nextTrainer != nullptr && nextTrainer->isOpen() &&                  // Destination trainer exists and is open
        (static_cast<int>(nextTrainer->getCustomers().size())) < nextTrainer->getCapacity() && // Destination has room for customers
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
            currTrainer->closeTrainer();
    }
    else
    {
        error("Cannot move customer");
    }
}


// Close Class
Close::Close(int id): // Constructor
trainerId(id)
{}

Close *Close::clone() {return new Close(*this);}

Close::~Close(){} // Deconstructor

// Getters
std::string Close::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
void Close::act(Studio &studio)
{
    vector<Customer*> temp;
    Trainer *trainer = studio.getTrainer(trainerId);
    temp = trainer->getCustomers();
    if (trainer == nullptr || !(trainer->isOpen()))
        error("Trainer does not exist or is not open");
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


// CloseAll Class
CloseAll::CloseAll(){} // Constructor

CloseAll *CloseAll::clone() {return new CloseAll(*this);}

CloseAll::~CloseAll(){} // Deconstructor

// Getters
std::string CloseAll::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
void CloseAll::act(Studio &studio)
{
    for (int i = 0; i < studio.getNumOfTrainers(); i++)
    {
        Trainer *currTrain = studio.getTrainer(i);
        if (currTrain->isOpen())
            cout << "Trainer " << i << " closed."<< " Salary " << std::to_string(currTrain->getSalary()) << "NIS" << endl;
    }
    complete();
}


// PrintWorkoutOptions Class
PrintWorkoutOptions::PrintWorkoutOptions(){} // Constructor

PrintWorkoutOptions *PrintWorkoutOptions::clone() {return new PrintWorkoutOptions(*this);}

PrintWorkoutOptions::~PrintWorkoutOptions(){} // Deconstructor

// Getters
std::string PrintWorkoutOptions::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
void PrintWorkoutOptions::act(Studio &studio)
{
    std::vector<Workout> wOptions = studio.getWorkoutOptions();
    for (Workout workout : wOptions)
    {
        std::string type;
        switch (workout.getType())
        {
        case ANAEROBIC:
            type = "Anaerobic";
            break;
        case CARDIO:
            type = "Cardio";
            break;
        case MIXED:
            type = "Mixed";
            break;
        }
        cout << workout.getName() + ", " + type + ", " + std::to_string(workout.getPrice()) << endl;
    }
    complete();
}


// PrintTrainerStatus Class
PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id){} // Constructor

PrintTrainerStatus *PrintTrainerStatus::clone() {return new PrintTrainerStatus(*this);}

PrintTrainerStatus::~PrintTrainerStatus(){} // Deconstructor

// Getters
std::string PrintTrainerStatus::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
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


// PrintActionsLog Class
PrintActionsLog::PrintActionsLog(){} // Constructor

PrintActionsLog *PrintActionsLog::clone() {return new PrintActionsLog(*this);}

PrintActionsLog::~PrintActionsLog(){} // Deconstructor

// Getters
std::string PrintActionsLog::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
void PrintActionsLog::act(Studio &studio)
{
    for (BaseAction *action : studio.getActionsLog())
        cout << action->getCalledAction() + " " + action->toString() << endl;
    complete();
}


// BackupStudio Class
BackupStudio::BackupStudio(){} // Constructor

BackupStudio *BackupStudio::clone() {return new BackupStudio(*this);}

BackupStudio::~BackupStudio(){} // Deconstructor

// Getters
std::string BackupStudio::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
void BackupStudio::act(Studio &studio)
{
    complete();
    delete backup;
    backup = new Studio(studio);
}


// RestoreStudio Class
RestoreStudio::RestoreStudio(){} // Constructor

RestoreStudio *RestoreStudio::clone() {return new RestoreStudio(*this);}

RestoreStudio::~RestoreStudio(){} // Deconstructor

// Getters
std::string RestoreStudio::toString() const
{
    std::string ret;
    getStatus() == COMPLETED ? ret = "Completed" : ret = "Error " + getErrorMsg();
    return ret;
}

// Actions
void RestoreStudio::act(Studio &studio)
{
    if (backup != nullptr)
    {
        studio = *backup;
        complete();
    }
    else
        error("No backup available");
}

