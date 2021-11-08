#include "Customer.h"

using namespace std;

// Concstructor
Customer::Customer(std::string c_name, int c_id):
    name(c_name),
    id(c_id)
    {};

Customer::Customer(const Customer& c_existing):
    name(c_existing.name),
    id(c_existing.id)
    {};

std::string Customer::getName() const 
{
    return name;
}

int Customer::getId() const 
{
    return id;
}

Customer::~Customer() 
{
    delete this;
}

// Sweaty Customer Constructor
SweatyCustomer::SweatyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
    {};

//Cheap Customer Copy Constructor
SweatyCustomer::SweatyCustomer(const SweatyCustomer& _sc):
    Customer::Customer(_sc.getName(), _sc.getId())
    {};

SweatyCustomer& SweatyCustomer::operator=(const SweatyCustomer& _sc)
{
    if (this == &_sc)
    {
        return *this;
    }
    delete this;
    //SweatyCustomer* temp = (_sc).clone();
    //this(_sc.clone());
    return *this;
}

SweatyCustomer::~SweatyCustomer() 
{
    delete this;
}

Customer* SweatyCustomer::clone()  
{
    return new SweatyCustomer::SweatyCustomer(this->getName(), this->getId());
}

// Cheap Customer Constructor
CheapCustomer::CheapCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

//Cheap Customer Copy Constructor
CheapCustomer::CheapCustomer(const CheapCustomer& _cc):
    Customer::Customer(_cc.getName(), _cc.getId())
    {};

Customer* CheapCustomer::clone()  
{
    return new CheapCustomer::CheapCustomer(this->getName(), this->getId());
}

// Heavy Muscle Customer Constructor
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

//Heavy Muscle Customer Copy Constructor
HeavyMuscleCustomer::HeavyMuscleCustomer(const HeavyMuscleCustomer& _hmc):
    Customer::Customer(_hmc.getName(),_hmc.getId())
    {};

Customer* HeavyMuscleCustomer::clone()  
{
    return new HeavyMuscleCustomer::HeavyMuscleCustomer(this->getName(), this->getId());
}

// Full Body Customer Constructor
FullBodyCustomer::FullBodyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

//Full Body Customer Copy Constructor
FullBodyCustomer::FullBodyCustomer(const FullBodyCustomer& _fbc):
    Customer::Customer(_fbc.getName(), _fbc.getId())
    {};

Customer* FullBodyCustomer::clone()  
{
    return new FullBodyCustomer::FullBodyCustomer(this->getName(), this->getId());
}
