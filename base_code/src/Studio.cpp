#include "../include/Studio.h"
#include "../include/Action.h"
#include <iostream>
#include <fstream>

using namespace std;

Studio::Studio():
open(false)
{} // Empty constructor

std::vector<std::string> *Studio::SplitSentence(const std::string &Sentence, char splt)
{
	std::string line("");
	std::vector<std::string> *text_by_lines = new std::vector<std::string>();
	char current_char;
	for (int i = 0; i < static_cast<int>(Sentence.size()); i++)
	{
		current_char = Sentence[i];
		if (current_char != splt)
		{
			line.push_back(current_char);
		}
		else
		{
			text_by_lines->push_back(line);
			line = "";
		}
	}
	text_by_lines->push_back(line);
	return text_by_lines;
}

Studio::Studio(const std::string &configFilePath):
open(true)
{ // Constructor with filepath
	std::string Text;
	ifstream MyReadFile(configFilePath);
	int data_type = 0;
	std::string workout_name("");
	WorkoutType workout;
	std::string workoutTypeStr;
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
			std::vector<std::string> *WordsFromCase_ = SplitSentence(Text, ',');
			workout_name = (*WordsFromCase_)[0];
			workoutTypeStr = (*WordsFromCase_)[1];
			
			if (workoutTypeStr == " Anaerobic")
			{
				workout = WorkoutType::ANAEROBIC;
			}
			else if (workoutTypeStr == " Mixed")
			{
				workout = WorkoutType::MIXED;
			}
		   	else if (workoutTypeStr == " Cardio")
			{
				workout = WorkoutType::CARDIO;
			}
			workout_price = std::stoi((*WordsFromCase_)[2]); // stoi function convert string to number.
			workout_options.push_back(Workout(workoutId, workout_name, workout_price, workout));
			workoutId++;
			delete WordsFromCase_;
		}
	}
	MyReadFile.close();
}

Studio::Studio(const Studio &StudioOther)
{ // Copy Constructor
	for (Trainer* trainer : StudioOther.trainers)
	{
		trainers.push_back(trainer->clone());
	}
	for (BaseAction* action : StudioOther.actionsLog)
	{
		actionsLog.push_back(action->clone());
	}
	for (Workout wrk : StudioOther.workout_options)
	{
		workout_options.push_back(Workout(wrk.getId(), wrk.getName(), wrk.getPrice(), wrk.getType()));
	}
}

Studio Studio::operator=(const Studio &StudioOther)
{ // Copy assignment
	if (this == &StudioOther)
	{ //self assgiment
		return *this;
	}
	else
	{
		for (Trainer* trainer : trainers)
		{
			delete trainer;
		}
		for (Trainer* trainer : StudioOther.trainers)
		{
			trainers.push_back(trainer);
		}
		for (BaseAction* action : actionsLog)
		{
			delete action;
		}
		for (BaseAction* action: StudioOther.actionsLog)
		{
			actionsLog.push_back(action);
		}
		workout_options.clear();
		for (Workout wrk : StudioOther.workout_options)
		{
			workout_options.push_back(Workout(wrk.getId(), wrk.getName(), wrk.getPrice(), wrk.getType()));
		}
	}
	return *this;
}

Studio::Studio(const Studio &&StudioOther)
{ // Move Constructor
	for (Trainer* trainer : StudioOther.trainers)
	{
		trainers.push_back(trainer);
	}
	for (BaseAction* action : StudioOther.actionsLog)
	{
		actionsLog.push_back(action);
	}
	for (Workout wrk : StudioOther.workout_options)
	{
		workout_options.push_back(wrk);
	}
}

Studio Studio::operator=(const Studio &&StudioOther)
{ // Move assigment
	if (this == &StudioOther)
	{
		return *this;
	}
	for (Trainer* trainer : trainers)
	{
		delete trainer;
	}
	for (Trainer* trainer : StudioOther.trainers)
	{
		trainers.push_back(trainer);
	}
	for (BaseAction* action : actionsLog)
	{
		delete action;
	}
	for (BaseAction* action : StudioOther.actionsLog)
	{
		actionsLog.push_back(action);
	}
	workout_options.clear();
	for (Workout wrk : StudioOther.workout_options)
	{
		workout_options.push_back(wrk);
	}
	return *this;
}

Studio::~Studio()
{
	for (Trainer *tr : trainers)
	{
		if (tr)
		{
			delete tr;
		}
	}
	
	for (BaseAction *ba : actionsLog)
	{
		delete ba;
	}
	//workout_options.clear(); // Might be useless
}

int Studio::getNumOfTrainers() const
{
	return trainers.size();
}
Trainer *Studio::getTrainer(int tid)
{
	if (tid < static_cast<int>(trainers.size()))
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
	return (tid >= 0 and tid < static_cast<int>(trainers.size()) && not trainers[tid]->isOpen());
}

void Studio::start()
{
	std::cout << "The Studio is now open!" << std::endl;
	int id = 0;
	open = true;
	vector<Customer *> customers;
	while (open) // Input loop
	{
		std::string sentence;
		getline(cin, sentence);
		std::vector<string> *input = Studio::SplitSentence(sentence, ' ');
		if ((*input)[0] == "open")
		{
			if (not canOpen(std::stoi((*input)[1]), (*input).size() - 2))
			{
				std::vector<Customer *> failed;
				OpenTrainer cantOpen = OpenTrainer(-1, failed);
				cantOpen.trigError("Workout session does not exist or is already open.", sentence);
				actionsLog.push_back(new OpenTrainer(cantOpen));
				continue;
			}
			
			int tid = std::stoi((*input)[1]);
			for (int i = 2; i < static_cast<int>((*input).size()); i++)
			{
				std::vector<string> *currentCustomer = Studio::SplitSentence((*input)[i], ',');
				std::string name = (*currentCustomer)[0];
				std::string type = (*currentCustomer)[1];
				if (type == "swt")
				{
					customers.push_back(new SweatyCustomer(name, id));
				}
				else if (type == "chp")
				{
					customers.push_back(new CheapCustomer(name, id));
				}
				else if (type == "mcl")
				{
					customers.push_back(new HeavyMuscleCustomer(name, id));
				}
				else if (type == "fbd")
				{
					customers.push_back(new FullBodyCustomer(name, id));
				}
				id++;
				delete currentCustomer;
				if (getTrainer(tid)->getCapacity() == static_cast<int>(customers.size()))
				{
					break;
				}
			}
			OpenTrainer currentTrainer(tid, customers);
			currentTrainer.act(*this);
			currentTrainer.setCalledAction(sentence);
			std::vector<Customer*> empty;
			OpenTrainer* push = new OpenTrainer(tid, empty);
			push->setCalledAction(sentence);
			push->setStatus();
			actionsLog.push_back(push);
		}
		else if ((*input)[0] == "order")
		{
			int id = std::stoi((*input)[1]);
			Order currentOrder = Order(id);
			currentOrder.act(*this);
			currentOrder.setCalledAction(sentence);
			actionsLog.push_back(new Order(currentOrder));
		}
		else if ((*input)[0] == "move")
		{
			int from = std::stoi((*input)[1]);
			int to = std::stoi((*input)[2]);
			int id = std::stoi((*input)[3]);
			MoveCustomer currentMove = MoveCustomer(from, to, id);
			currentMove.act(*this);
			currentMove.setCalledAction(sentence);
			actionsLog.push_back(new MoveCustomer(currentMove));
		}
		else if ((*input)[0] == "close")
		{
			int tid = std::stoi((*input)[1]);;
			Close closeTrainer = Close(tid);
			closeTrainer.act(*this);
			closeTrainer.setCalledAction(sentence);
			actionsLog.push_back(new Close(closeTrainer));
		}
		else if ((*input)[0] == "closeall")
		{
		
			CloseAll close = CloseAll();
			close.act(*this);
			close.setCalledAction(sentence);
			actionsLog.push_back(new CloseAll(close));
			open = false;
		}
		else if ((*input)[0] == "workout_options")
		{
			PrintWorkoutOptions prt = PrintWorkoutOptions();
			prt.act(*this);
			prt.setCalledAction(sentence);
			actionsLog.push_back(new PrintWorkoutOptions(prt));
		}
		else if ((*input)[0] == "status")
		{
			int tid = std::stoi((*input)[1]);
			PrintTrainerStatus prt = PrintTrainerStatus(tid);
			prt.act(*this);
			prt.setCalledAction(sentence);
			actionsLog.push_back(new PrintTrainerStatus(prt));
		}
		else if ((*input)[0] == "log")
		{
			PrintActionsLog prt = PrintActionsLog();
			prt.act(*this);
			prt.setCalledAction(sentence);
			actionsLog.push_back(new PrintActionsLog(prt));
		}
		else if ((*input)[0] == "backup")
		{
			BackupStudio bck = BackupStudio();
			bck.act(*this);
			bck.setCalledAction(sentence);
			actionsLog.push_back(new BackupStudio(bck));
		}
		else if ((*input)[0] == "restore")
		{
			RestoreStudio rst = RestoreStudio();
			rst.act(*this);
			rst.setCalledAction(sentence);
			actionsLog.push_back(new RestoreStudio(rst));
		}
	delete input;
	}
}