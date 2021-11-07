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

void Customer::clone(Customer* c_existing)
{
    
}
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

// Cheap Customer Constructor
CheapCustomer::CheapCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

// Heavy Muscle Customer Constructor
HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};

// Full Body Customer Constructor
FullBodyCustomer::FullBodyCustomer(std::string name, int id): 
    Customer::Customer(name, id)
{};