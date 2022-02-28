#ifndef TRAINER_H_
#define TRAINER_H_

#include "Customer.h"
#include "Workout.h"

#include <vector>
#include <algorithm>
#include <iostream>

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    // Rule of Five
    Trainer(int t_capacity); // Constructor
    Trainer* clone();
    Trainer(const Trainer& t); // Copy constructor
    Trainer& operator=(const Trainer& t); // Copy assignment
    Trainer(Trainer&& t); // Move constructor
    Trainer& operator=(Trainer&& t); // Move assignment
    ~Trainer(); // Deconstructor

    // Getters
    int getCapacity() const;
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    int getSalary() const;
    bool isOpen() const;
    std::string getStatus();
    int getRemainingSlots() const;

    // Actions
    void addOrder(OrderPair order);
    void addCustomer(Customer* customer);
    void removeOrders(int cid, bool sal); // Removes orders, boolean as a check to reduce salary or not.
    void removeCustomer(int id);
    void removeCustomerWithSalary(int id); // Removes customer and reduces salary (removeOrders(cid, true))
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    int salary;
};

#endif