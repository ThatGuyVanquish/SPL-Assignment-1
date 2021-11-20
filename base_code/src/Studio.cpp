#include "../include/Studio.h"
#include "../include/Action.h"
#include <iostream>
#include <fstream>
using namespace std;
Studio::Studio() {} // Empty constructor

std::vector<std::string> *SplitSentence(const std::string &Sentence, char splt); // Forward declaration

Studio::Studio(const std::string &configFilePath):open(true)
{ // Constructor with filepath
	string Text;
	ifstream MyReadFile(configFilePath);
	int data_type = 0;
	std::string workout_name("");
	WorkoutType workout;
	std::string workoutTypeStr;
	std::vector<std::string> *WordsFromCase_;
	int workout_price;
	int workoutId = 0;
	while (getline(MyReadFile, Text))
	{
		if (Text.empty())
		{
			continue;
		}
		if (Text[0] == '#')
		{
			data_type++;
		}
		else if (data_type == 2)
		// 1 is unnecessary because we can count number of different capacities
		{
			std::vector<std::string> *text_by_lines = SplitSentence(Text, ',');
			for (std::string str : *text_by_lines)
			{
				trainers.push_back(new Trainer(stoi(str)));
			}
			delete text_by_lines;
		}
		else if (data_type == 3)
		{
			WordsFromCase_ = SplitSentence((Text), ',');
			workout_name = (*WordsFromCase_)[0];
			workoutTypeStr = (*WordsFromCase_)[1];
			if (workoutTypeStr == "Anaerobic")
			{
				workout = WorkoutType::ANAEROBIC;
			}
			if (workoutTypeStr == "Mixed")
			{
				workout = WorkoutType::MIXED;
			}
			if (workoutTypeStr == "Cardio")
			{
				workout = WorkoutType::CARDIO;
			}
			workout_price = stoi((*WordsFromCase_)[2]); // stoi function convert string to number.
			workout_options.push_back(Workout(workoutId, workout_name, workout_price, workout));
			workoutId++;
			delete WordsFromCase_;
		}
	}
	MyReadFile.close();
}

Studio::Studio(const Studio &StudioOther)
{ // Copy Constructor
	for (int i = 0; i < StudioOther.trainers.size(); i++)
	{
		trainers.push_back(StudioOther.trainers[i]->clone());
	}
	for (int i = 0; i < StudioOther.actionsLog.size(); i++)
	{

		actionsLog.push_back(StudioOther.actionsLog[i]->clone());
	}
	workout_options = StudioOther.workout_options;
}

Studio Studio::operator=(const Studio &StudioOther)
{ // Copy assignment
	if (this == &StudioOther)
	{ //self assgiment
		return *this;
	}
	else
	{
		for (int i = 0; i < trainers.size(); i++)
		{

			delete trainers[i];
		}
		for (int i = 0; i < StudioOther.trainers.size(); i++)
		{

			trainers.push_back(StudioOther.trainers[i]->clone());
		}
		for (int i = 0; i < actionsLog.size(); i++)
		{

			delete actionsLog[i];
		}
		for (int i = 0; i < StudioOther.actionsLog.size(); i++)
		{

			actionsLog.push_back(StudioOther.actionsLog[i]->clone());
		}
		workout_options = StudioOther.workout_options;
	}
}

Studio::Studio(const Studio &&StudioOther)
{ // Move Constructor
	for (int i = 0; i < StudioOther.trainers.size(); i++)
	{
		trainers.push_back(StudioOther.trainers[i]); // not sure we need clone because this is an rvalue ref
	}
	for (int i = 0; i < StudioOther.actionsLog.size(); i++)
	{
		actionsLog.push_back(StudioOther.actionsLog[i]); // not sure we need clone because this is an rvalue ref
	}
	workout_options = StudioOther.workout_options;
}

Studio Studio::operator=(const Studio &&StudioOther)
{ // Move assigment
	if (this == &StudioOther)
	{
		return *this;
	}
	for (int i = 0; i < trainers.size(); i++)
	{
		delete trainers[i];
	}
	for (int i = 0; i < StudioOther.trainers.size(); i++)
	{
		trainers.push_back(StudioOther.trainers[i]); // not sure we need clone because this is an rvalue ref
	}
	for (int i = 0; i < actionsLog.size(); i++)
	{
		delete actionsLog[i];
	}
	for (int i = 0; i < StudioOther.actionsLog.size(); i++)
	{
		actionsLog.push_back(StudioOther.actionsLog[i]); // not sure we need clone because this is an rvalue ref
	}
	workout_options = StudioOther.workout_options;
	return *this;
}

Studio::~Studio()
{
	for (Trainer *tr : trainers)
	{
		delete tr;
	}
	for (BaseAction *ba : actionsLog)
	{
		delete ba;
	}
	workout_options.clear(); // Might be useless
}

int Studio::getNumOfTrainers() const
{
	return trainers.size();
}
Trainer *Studio::getTrainer(int tid)
{
	if (tid < trainers.size())
	{
		return trainers[tid];
	}
	return nullptr;
}

const std::vector<BaseAction *> &Studio::getActionsLog() const
{
	return actionsLog;
} // Return a reference to the history of actions

std::vector<Workout> &Studio::getWorkoutOptions()
{
	return workout_options;
}

bool Studio::canOpen(int tid, int numOfCustomers)
{
	return (tid >= 0 and tid < trainers.size() && not trainers[tid]->isOpen());
}

void Studio::start()
{
	std::cout << "The Studio is now open!" << std::endl;
	int id = 0;
	open = true;
	while (open) // Input loop
	{
		std::string sentence;
		getline(cin, sentence);
		std::vector<string> *input = SplitSentence(sentence, ' ');	
		if ((*input)[0] == "open")
		{
			if (not canOpen(std::stoi((*input)[1]), (*input).size() - 2))
			{
				std::vector<Customer *> failed;
				OpenTrainer::OpenTrainer cantOpen(-1, failed);
				cantOpen.trigError("Workout session does not exist or is already open.", sentence);
				continue;
			}
			vector<Customer*> customers;
			int tid = std::stoi((*input)[1]);
			for (int i = 2; i < (*input).size(); i++)
			{
				std::vector<string> *currentCustomer = SplitSentence((*input)[i], ',');
				std::string name = (*currentCustomer)[0];
				std::string type = (*currentCustomer)[1];
				Customer* c;
				if (type == "swt")
				{
					c = new SweatyCustomer(name, id);	
				}
				else if (type == "chp")
				{
					c = new CheapCustomer(name, id);
				}
				else if (type == "mcl")
				{
					c = new HeavyMuscleCustomer(name, id);
				}
				else if (type == "fbc")
				{
					c = new FullBodyCustomer(name, id);
				}
				id++;
				customers.push_back(c);
				delete currentCustomer;
				if (getTrainer(tid)->getCapacity() == customers.size())
				{
					break;
				}
			}
			OpenTrainer::OpenTrainer currentTrainer(tid, customers);
			currentTrainer.act(*this);
			currentTrainer.setCalledAction(sentence);
			actionsLog.push_back(new OpenTrainer(currentTrainer));
		}
		else if ((*input)[0] == "order")
		{
			int id = std::stoi((*input)[1]);
			Order::Order currentOrder(id);
			currentOrder.act(*this);
			currentOrder.setCalledAction(sentence);
			actionsLog.push_back(new Order(currentOrder));
		}
		else if ((*input)[0] == "move")
		{
			int from = std::stoi((*input)[1]);
			int to = std::stoi((*input)[2]);
			int id = std::stoi((*input)[3]);
			MoveCustomer::MoveCustomer currentMove(from, to, id);
			currentMove.act(*this);
			currentMove.setCalledAction(sentence);
			actionsLog.push_back(new MoveCustomer(currentMove));
		}
	}