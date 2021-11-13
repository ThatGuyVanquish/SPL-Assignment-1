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
    int getSalary();
    void Trainer::removeOrders(int start, int end);
    void Trainer::addOrder(OrderPair& order);
    bool isOpen();
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
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