#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity); // Constructor
    Trainer(const Trainer& t); // Copy Constructor
    Trainer& operator=(const Trainer& t); // Copy assignment
    Trainer(const Trainer&& t); // Move Constructor
    Trainer& operator=(const Trainer&& t); // Move assignment
    ~Trainer(); // Destructor
    int getCapacity() const;
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    int getSalary() const;
    void removeOrders(int cid, bool sal); // Removes orders, boolean as a check to reduce salary or not.
    void addOrder(OrderPair order);
    bool isOpen() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    void removeCustomerWithSalary(int id); // Removes customer and reduces salary (removeOrders(cid, true))
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    std::string getStatus();
    int getRemainingSlots() const;
    Trainer* clone();
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
    int salary;
};


#endif