#include "Trainer.h"
#include <vector>

using namespace std;

//Trainer Constructor
Trainer::Trainer(int t_capacity): 
    capacity(t_capacity)
    {};

int Trainer::getCapacity() const 
    {
        return capacity;
    }

void Trainer::addCustomer(Customer* customer) 
{
    capacity++;
    customersList.insert(customersList.begin()+capacity, customer);
}

void Trainer::removeCustomer(int id) 
{
    int pos = 0;
    for (Customer*& c : customersList)
    {
        if (c->getId() == id)
            {
            customersList.erase(customersList.begin() + pos);
            capacity--;
            break;
            }
        pos++;
    }
}

Customer* Trainer::getCustomer(int id)
{
    for (Customer*& c : customersList)
        if (c->getId() == id)
            return c;
}

std::vector<Customer*>& Trainer::getCustomers() 
{
    return customersList;
}

std::vector<OrderPair>& Trainer::getOrders() {
    return orderList;
}

// void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options):{};

void Trainer:: openTrainer() {
    if (customersList.size() < capacity)
        open = true;
}