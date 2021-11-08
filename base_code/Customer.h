#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Workout.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    Customer(const Customer& c_existing);
    ~Customer();
    virtual Customer* clone();
    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;
private:
    const std::string name;
    const int id;
};

class SweatyCustomer : public Customer {
public:
	SweatyCustomer(std::string name, int id);
    SweatyCustomer(const SweatyCustomer& _cs);
    SweatyCustomer& operator=(const SweatyCustomer& _sc);
    ~SweatyCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    virtual Customer* clone() override;
private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
    CheapCustomer(const CheapCustomer& _cc);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    virtual Customer* clone() override;
private:
};


class HeavyMuscleCustomer : public Customer {
public:
	HeavyMuscleCustomer(std::string name, int id);
    HeavyMuscleCustomer(const HeavyMuscleCustomer& _hmc);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    virtual Customer* clone() override;
private:
};


class FullBodyCustomer : public Customer {
public:
	FullBodyCustomer(std::string name, int id);
    FullBodyCustomer(const FullBodyCustomer& _fbc);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    virtual Customer* clone() override;
private:
};


#endif