#include "Studio.h"
#include "Action.h"
#include <iostream>
#include <fstream>
using namespace std;
Studio::Studio() {} // Empty constructor

std::vector<std::string> *SplitSentence(const std::string &Sentence, char splt); // Forward declaration

Studio::Studio(const std::string &configFilePath)
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
		// 1 Is unnecessary because we can count number of different capacities
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
	return (tid < trainers.size() && not trainers[tid]->isOpen() && trainers[tid]->getCapacity() - (trainers[tid]->getCustomers()).size() > numOfCustomers);
}

void Studio::start()
{
	std::cout << "The Studio is now open!" << std::endl;
	int id = 0;
	std::string text;
	std::string word;
	while (true) // Input loop
	{
		cin >> text;
		std::vector<string> *input = SplitSentence(text, ' ');
		if ((*input)[0] == "open")
		{
			if (not canOpen(std::stoi((*input)[1]), (*input).size() - 2))
			{
				std::vector<Customer *> failed;
				OpenTrainer::OpenTrainer cantOpen(-1, failed);
				cantOpen.trigError("Trainer ID is invalid or not enough capacity", text);
				continue;
			}
			vector<Customer *> customers;
			for (int i = 2; i < (*input).size(); i++)
			{
				std::vector<string> *currentCustomer = SplitSentence((*input)[i], ',');
				std::string name = (*currentCustomer)[0];
				std::string type = (*currentCustomer)[1];
				if (type == "swt")
				{
					SweatyCustomer *c = new SweatyCustomer(name, id);
					customers.push_back(c);
					id++;
				}
				if (type == "chp")
				{
					CheapCustomer *c = new CheapCustomer(name, id);
					customers.push_back(c);
					id++;
				}
				if (type == "mcl")
				{
					HeavyMuscleCustomer *c = new HeavyMuscleCustomer(name, id);
					customers.push_back(c);
					id++;
				}
				if (type == "fbc")
				{
					FullBodyCustomer *c = new FullBodyCustomer(name, id);
					customers.push_back(c);
					id++;
				}
			}
			OpenTrainer currentTrainer = OpenTrainer((*input)[1], customers);
			currentTrainer.act(*this);
			actionsLog.push_back(*currentTrainer);
		}
		/*if (input[0] == "order")
		{
			int id = std::stoi(input[1]);
			Order currentOrder = Order::Order(id);
			currentOrder.act(studio);
			maybe a print order here if we move the print from act to toString
		}
		if (input[0] == "move")
		{
			int from = input[1];
			int to = input[2];
			int id = input[3];
			we gotta perform checks to see if : origin trainer exists and his session is open
													destination trainer exists and is open
														the customer with said id is in origin trainers session
															the destination trainer has capacity
																MoveCustomer currentMove = MoveCustomer::MoveCustomer(from, to, id);
			currentMove.act(studio);
		*/
		}
	}