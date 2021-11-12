#include "Trainer.h"
#include <bits/stdc++.h>

using namespace std;

// Constructor
Trainer::Trainer(int t_capacity): 
    capacity(t_capacity),
    open(false),
    customersList(),
    orderList()
    {};

// Copy Constructor
Trainer::Trainer(const Trainer& t):
    capacity(t.capacity), 
    open(t.open),
    customersList(t.customersList),
    orderList(t.orderList),
    salary(0)
    {};

// Copy Assignment
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
            customersList.push_back(customer);
        orderList = t.orderList;
    }
}

// Move Constructor
Trainer::Trainer(const Trainer&& t):
    capacity(t.capacity),
    open(t.open),
    customersList(),
    orderList(),
    salary(t.salary)
{
    //t.open = NULL;
    // Move the pairs to new orderList in reverse order (same as pop order), then reverse
    for (int i = t.orderList.size()-1; i--;)
    {
        orderList.push_back(t.orderList[i]);
        //t.orderList.pop_back();
        i++;
    }
    std::reverse(orderList.begin(), orderList.end());
}

// Move Assignment
Trainer& Trainer::operator=(const Trainer&& t)
{
    if (this != &t)
    {
        capacity = t.capacity;
        open = t.open;
        salary = t.salary;
        //t.open = NULL;
        for (Customer* customer : customersList)
        {
            customer = nullptr;
        }
        int i = 0;
        for (Customer* customer: t.customersList)
        {
            customersList.push_back(customer);
            //t.customersList[i] = nullptr;
            i++;
        }
        orderList.clear();
        for (int i = t.orderList.size()-1; i--;)
        {
            orderList.push_back(t.orderList[i]);
            //t.orderList.pop_back();
            i++;
        }
        std::reverse(orderList.begin(), orderList.end());
    }
    return *this;
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

// void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options):{};

void Trainer::openTrainer() 
{
    open = true;
}

void Trainer::closeTrainer() 
{
    open = false;
}