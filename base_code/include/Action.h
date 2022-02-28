#ifndef ACTION_H_
#define ACTION_H_

#include "Customer.h"
#include "../include/Trainer.h"
#include "../include/Studio.h"

#include <iostream>

using namespace std;

enum ActionStatus{
    COMPLETED, ERROR
};

class Studio;

class BaseAction{
public:
    BaseAction();
    virtual void act(Studio& studio) = 0;
    virtual BaseAction* clone() = 0;
    virtual ~BaseAction();

    // Getters
    ActionStatus getStatus() const;
    std::string getCalledAction();
    virtual std::string toString() const = 0;
    
    // Actions
    void trigError(std::string err, std::string input);
    void setCalledAction(std::string action); // Saves input in calledAction to be recalled in PrintActionsLog
    void setStatus();

protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;

private:
    std::string errorMsg;
    ActionStatus status;
    std::string calledAction;
};


class OpenTrainer : public BaseAction {
public:
    OpenTrainer(int id, std::vector<Customer *> &customersList);
    OpenTrainer* clone() override;
    ~OpenTrainer();

    // Getters
    std::string toString() const;
    std::vector<Customer*> getCustomers();

    // Actions
    void act(Studio &studio);

private:
	const int trainerId;
	std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    Order(int id);
    Order* clone() override;
    ~Order();

    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
    
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    MoveCustomer* clone() override;
    ~MoveCustomer();

    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
    
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    Close* clone() override;
    ~Close();
    
    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
    
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    CloseAll* clone() override;
    ~CloseAll();
    
    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    ~PrintWorkoutOptions();
    PrintWorkoutOptions* clone() override;

    // Getters
    std::string toString() const;
    
    // Actions
    void act(Studio &studio);
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    PrintTrainerStatus* clone() override;
    ~PrintTrainerStatus();
    
    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
    
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    PrintActionsLog* clone() override;
    ~PrintActionsLog();
    
    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    BackupStudio* clone() override;
    ~BackupStudio();
    
    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    RestoreStudio* clone() override;
    ~RestoreStudio();
    
    // Getters
    std::string toString() const;

    // Actions
    void act(Studio &studio);
};

#endif