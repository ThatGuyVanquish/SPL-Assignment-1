#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    Trainer(const Trainer& t);
    Trainer& operator=(const Trainer& t);
    Trainer(const Trainer&& t);
    Trainer& operator=(const Trainer&& t);
    ~Trainer();
    int getCapacity() const;
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    int getSalary() const;
    void Trainer::removeOrders(int cid, bool salary);
    void Trainer::addOrder(OrderPair& order);
    bool isOpen() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    void removeCustomerWithSalary(int id, bool salary);
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