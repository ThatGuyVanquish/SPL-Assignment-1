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
    ~OpenTrainer();
    void act(Studio &studio);
    std::string toString() const;
    OpenTrainer* clone() override;
    std::vector<Customer*> getCustomers();
private:
	const int trainerId;
	std::vector<Customer *> customers;
};


class Order : public BaseAction {
public:
    Order(int id);
    ~Order();
    void act(Studio &studio);
    std::string toString() const;
    Order* clone() override;
private:
    const int trainerId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    ~MoveCustomer();
    void act(Studio &studio);
    std::string toString() const;
    MoveCustomer* clone() override;
private:
    const int srcTrainer;
    const int dstTrainer;
    const int id;
};


class Close : public BaseAction {
public:
    Close(int id);
    ~Close();
    void act(Studio &studio);
    std::string toString() const;
    Close* clone() override;
private:
    const int trainerId;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    ~CloseAll();
    void act(Studio &studio);
    std::string toString() const;
    CloseAll* clone() override;
private:
};


class PrintWorkoutOptions : public BaseAction {
public:
    PrintWorkoutOptions();
    ~PrintWorkoutOptions();
    void act(Studio &studio);
    std::string toString() const;
    PrintWorkoutOptions* clone() override;
private:
};


class PrintTrainerStatus : public BaseAction {
public:
    PrintTrainerStatus(int id);
    ~PrintTrainerStatus();
    void act(Studio &studio);
    std::string toString() const;
    PrintTrainerStatus* clone() override;
private:
    const int trainerId;
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    ~PrintActionsLog();
    void act(Studio &studio);
    std::string toString() const;
    PrintActionsLog* clone() override;
private:
};


class BackupStudio : public BaseAction {
public:
    BackupStudio();
    ~BackupStudio();
    void act(Studio &studio);
    std::string toString() const;
    BackupStudio* clone() override;
private:
};


class RestoreStudio : public BaseAction {
public:
    RestoreStudio();
    ~RestoreStudio();
    void act(Studio &studio);
    std::string toString() const;
    RestoreStudio* clone() override;
};


#endif