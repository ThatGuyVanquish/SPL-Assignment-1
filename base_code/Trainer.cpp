#include "Trainer.h"
#include <algorithm>

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
    customersList(),
    orderList(),
    salary(t.salary)
    {
        for (Customer* customer : t.customersList)
        {
            customersList.push_back(customer->clone());
        }
        for (OrderPair order : t.orderList)
        {
            orderList.push_back(OrderPair(order.first, order.second));
        }
    };

// Copy Assignment
Trainer& Trainer::operator=(const Trainer& t)
{
    if (this!= &t)
    {
        capacity = t.capacity;
        open = t.open;
        salary = t.salary;
        for (Customer* customer : customersList)
            delete customer;
        customersList.clear();
        for (Customer* customer : t.customersList)
            customersList.push_back(customer->clone());
        orderList.clear();
        for (OrderPair order : t.orderList)
        {
            orderList.push_back(OrderPair(order.first, order.second));
        }
    }
    return *this;
}

// Move Constructor
Trainer::Trainer(const Trainer&& t):
    capacity(t.capacity),
    open(t.open),
    customersList(),
    orderList(),
    salary(t.salary)
{
    for (Customer* customer : t.customersList)
    {
        customersList.push_back(customer->clone());
        delete customer;
    }
    for (OrderPair order : t.orderList)
    {
        orderList.push_back(order);
    }
    delete &t;
}

// Move Assignment
Trainer& Trainer::operator=(const Trainer&& t)
{
    if (this != &t)
    {
        capacity = t.capacity;
        open = t.open;
        salary = t.salary;
        for (Customer* customer : customersList)
        {
            delete customer;
        }
        customersList.clear();
        for (Customer* customer: t.customersList)
        {
            customersList.push_back(customer);
        }
        orderList.clear();
        for (OrderPair order : t.orderList)
        {
            orderList.push_back(order);
        }
        delete &t;
    }
    return *this;
}

Trainer* Trainer::clone()
{
    return new Trainer(*this);
}

Trainer::~Trainer()
{
    open = NULL;
    salary = 0;
    capacity = 0;
    for (Customer* customer : customersList)
    {
        delete customer;
    }
    customersList.clear();
    orderList.clear();
}

int Trainer::getCapacity() const 
    {
        return capacity;
    }

int Trainer::getRemainingSlots() const
    {
        return capacity-customersList.size();
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

void Trainer::addOrder(OrderPair& order) // Might need to make it pass by value
{
    salary = salary + order.second.getPrice();
    orderList.push_back(order);
}

int Trainer::getSalary() const
{
    return salary;
}

bool Trainer::isOpen() const
{
    return open;
}

void Trainer::addCustomer(Customer* customer) 
{
    customersList.push_back(customer);
}

void Trainer::removeOrders(int cid, bool salary)
{
    int start = 0;
    int end = 0;
    bool stop = false;
    std::vector<OrderPair> newOrders;
    for (OrderPair order : orderList)
    {
        if(order.first == cid)
        {
            order.first = -1;
        }
        else 
        {
            newOrders.push_back(order);
            if (salary)
            {
                salary = salary - order.second.getPrice();
            }
        }
    }
    orderList.clear();
    orderList = newOrders;
}

void Trainer::removeCustomer(int id) 
{
    int pos = 0;
    for (Customer*& customer : customersList)
    {
        if (customer->getId() == id)
            {
                delete customer;
                customersList.erase(customersList.begin() + pos);
                capacity--;
                break;
            }
        pos++;
    }
    removeOrders(id, false);
}

void Trainer::removeCustomerWithSalary(int cid, bool salary)
{
        int pos = 0;
    for (Customer*& customer : customersList)
    {
        if (customer->getId() == cid)
            {
                delete customer;
                customersList.erase(customersList.begin() + pos);
                capacity--;
                break;
            }
        pos++;
    }
    removeOrders(cid, true);
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options)
{
    for (int workout : workout_ids)
    {
        OrderPair temp(customer_id, workout_options[workout]);
        addOrder(temp);
    }
}

void Trainer::openTrainer() 
{
    open = true;
}

void Trainer::closeTrainer() 
{
    open = false;
    for (Customer* customer : customersList)
    {
        removeCustomer(customer->getId());
    }
}

std::string Trainer::getStatus()
{
    if (isOpen())
    {
        return "open";
    }
    return "closed";
}