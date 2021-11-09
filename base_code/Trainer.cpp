#include "Trainer.h"

using namespace std;

//Trainer Constructor
Trainer::Trainer(int t_capacity): 
    capacity(t_capacity),
    open(false),
    customersList(),
    orderList()
    {};

//Trainer Copy Constructor
Trainer::Trainer(const Trainer& t):
    capacity(t.capacity), 
    open(t.open),
    customersList(t.customersList),
    orderList(t.orderList),
    salary(0)
    {};

//Trainer Copy Assignment
Trainer& Trainer::operator=(const Trainer& t)
{
    if (this!= &t)
    {
        capacity = t.capacity;
        open = t.open;
        for (Customer* customer : customersList)
            delete customer;
        customersList.clear();
        for (Customer* customer : t.customersList)
            customersList.push_back(customer->clone());
        orderList = t.orderList;
    }
}

int Trainer::getCapacity() const 
    {
        return capacity;
    }

void Trainer::addCustomer(Customer* customer) 
{
    if (customersList.size() < capacity)
        customersList.push_back(customer);
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

std::vector<OrderPair>& Trainer::getOrders() 
{
    return orderList;
}

// void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options):{};

void Trainer::openTrainer() 
{
    open = true;
}

void Trainer::closeTrainer() 
{
    open = false;
}

int Trainer::getSalary() 
{
    for (OrderPair& order : orderList) 
    {
        salary += order.second.getPrice();
    }
    return salary;
}

bool Trainer::isOpen() 
{
    return open;
}