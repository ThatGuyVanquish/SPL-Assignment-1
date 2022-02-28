#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "Workout.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual Customer* clone() = 0;
    virtual ~Customer();

    // Getters
    int getId() const;
    std::string getName() const;
    virtual std::string toString() const = 0;
    bool orderStatus(); // Returns if a customer has ordered already (I.E. was in the customerlist of a trainer on which 'order' was called)
    
    // Actions
    virtual std::vector<int> order(const std::vector<Workout> &workout_options) = 0;
    void reqOrder(); // Switches hasOrdered field to true

private:
    const std::string name;
    const int id;
    bool hasOrdered;
};

/*
**** Sweaty Customer ****
Order strategy:
Orders all of the available cardio workouts, by the order they've been received in the config file.
*/

class SweatyCustomer : public Customer {
public:
	SweatyCustomer(std::string name, int id);
    SweatyCustomer* clone() ;
    ~SweatyCustomer();

    // Getters
    std::string toString() const;

    // Actions
    std::vector<int> order(const std::vector<Workout> &workout_options);
};

/*
**** Cheap Customer ****
Order strategy:
Orders cheapest workout available.
*/

class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
    CheapCustomer* clone() ;
    ~CheapCustomer();

    // Getters
    std::string toString() const;

    // Actions
    std::vector<int> order(const std::vector<Workout> &workout_options);
};


class HeavyMuscleCustomer : public Customer {
public:
	HeavyMuscleCustomer(std::string name, int id);
    HeavyMuscleCustomer* clone() ;
    ~HeavyMuscleCustomer();

    // Getters
    std::string toString() const;

    // Actions
    std::vector<int> order(const std::vector<Workout> &workout_options);
};


class FullBodyCustomer : public Customer {
public:
	FullBodyCustomer(std::string name, int id);
    FullBodyCustomer* clone() ;
    ~FullBodyCustomer();

    // Getters
    std::string toString() const;

    // Actions
    std::vector<int> order(const std::vector<Workout> &workout_options);
};

#endif