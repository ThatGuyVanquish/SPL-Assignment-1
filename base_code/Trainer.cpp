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

Trainer::~Trainer()
{
    open = NULL;
    salary = 0;
    capacity = 0;
    customersList.clear();
    orderList.clear();
}

int Trainer::getCapacity() const 
    {
        return capacity;
    }

Customer* Trainer::getCustomer(int id)
{
    for (Customer*& c : customersList)
        if (c->getId() == id)
            return c;
    return nullptr;
}

std::vector<Customer*>& Trainer::getCustomers() 
{
    return customersList;
}

std::vector<OrderPair>& Trainer::getOrders() 
{
    return orderList;
}

void Trainer::calcSalary() 
{
    for (OrderPair& order : orderList) 
    {
        salary += order.second.getPrice();
    }
}

void Trainer::removeOrders(int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        salary = salary - orderList[i].second.getPrice();
    }
    orderList.erase(orderList.begin()+start, orderList.begin()+end);
}

void Trainer::addOrder(OrderPair& order) // Might need to make it pass by value
{
    orderList.push_back(order);
}

int Trainer::getSalary()
{
    return salary;
}

bool Trainer::isOpen() 
{
    return open;
}

void Trainer::addCustomer(Customer* customer) 
{
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

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options)
{
    for (int workout : workout_ids)
    {
        orderList.push_back(OrderPair(customer_id, workout_options[workout]));
    }
}

void Trainer::openTrainer() 
{
    open = true;
}

void Trainer::closeTrainer() 
{
    open = false;
}