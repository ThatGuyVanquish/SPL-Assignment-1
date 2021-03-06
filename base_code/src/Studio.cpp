#include "../include/Studio.h"

std::vector<std::string> *Studio::splitLine(const std::string &line, char delimeter)
{
	std::string currentWord("");
	std::vector<std::string> *configLines = new std::vector<std::string>();
	char currentChar;
	for (int i = 0; i < static_cast<int>(line.size()); i++)
	{
		currentChar = line[i];
		if (currentChar != delimeter)
			currentWord.push_back(currentChar);
		else
		{
			configLines->push_back(currentWord);
			currentWord = "";
		}
	}
	configLines->push_back(line);
	return configLines;
}


Studio::Studio():
open(false),
_cid(0)
{} 

Studio::Studio(const std::string &configFilePath): // Constructor with filepath
open(true),
_cid(0)
{ 
	std::string currentLine;
	ifstream configFile(configFilePath);
	int configCounter = 0;
	std::string workoutName("");
	WorkoutType workout;
	std::string workoutTypeStr;
	int workoutPrice;
	int workoutId = 0;
	while (getline(configFile, currentLine))
	{
		if (currentLine.empty())
			continue;
		if (currentLine[0] == '#')
			configCounter++;
		else if (configCounter == 2)
		// 1 is unnecessary because we can count number of different capacities
		{
			std::vector<std::string> *configLines = splitLine(currentLine, ',');
			for (std::string str : *configLines)
				trainers.push_back(new Trainer(stoi(str)));
			delete configLines;
		}
		else if (configCounter == 3)
		{
			std::vector<std::string> *currentWorkout = splitLine(currentLine, ',');
			workoutName = (*currentWorkout)[0];
			workoutTypeStr = (*currentWorkout)[1];
			
			if (workoutTypeStr == " Anaerobic")
				workout = WorkoutType::ANAEROBIC;
			else if (workoutTypeStr == " Mixed")
				workout = WorkoutType::MIXED;
		   	else if (workoutTypeStr == " Cardio")
				workout = WorkoutType::CARDIO;

			workoutPrice = std::stoi((*currentWorkout)[2]);
			workout_options.push_back(Workout(workoutId, workoutName, workoutPrice, workout));
			workoutId++;
			delete currentWorkout;
		}
	}
	configFile.close();
}

Studio::Studio(const Studio &StudioOther): 
open(StudioOther.open),
_cid(StudioOther._cid)
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

Studio& Studio::operator=(const Studio &StudioOther)
{ // Copy assignment
	if (this == &StudioOther)
	{ //self assgiment
		return *this;
	}
	else
	{
		open = StudioOther.open;
		_cid = StudioOther._cid;
		for (Trainer* trainer : trainers)
		{
			delete trainer;
		}
		trainers.clear();
		for (Trainer* trainer : StudioOther.trainers)
		{
			trainers.push_back(trainer->clone());
		}
		for (BaseAction* action : actionsLog)
		{
			delete action;
		}
		actionsLog.clear();
		for (BaseAction* action: StudioOther.actionsLog)
		{
			actionsLog.push_back(action->clone());
		}
		workout_options.clear();
		for (Workout wrk : StudioOther.workout_options)
		{
			workout_options.push_back(Workout(wrk.getId(), wrk.getName(), wrk.getPrice(), wrk.getType()));
		}
	}
	return *this;
}

Studio::Studio(Studio &&StudioOther):
open(StudioOther.open),
_cid(StudioOther._cid)
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
	StudioOther.trainers.clear();
	StudioOther.actionsLog.clear();
	StudioOther.workout_options.clear();
	StudioOther.open = false;
	StudioOther._cid = 0;
}

Studio& Studio::operator=(Studio &&StudioOther)
{ // Move assigment
	if (this == &StudioOther)
	{
		return *this;
	}
	open = StudioOther.open;
	_cid = StudioOther._cid;
	for (Trainer* trainer : trainers)
	{
		delete trainer;
	}
	trainers.clear();
	for (Trainer* trainer : StudioOther.trainers)
	{
		trainers.push_back(trainer);
	}
	for (BaseAction* action : actionsLog)
	{
		delete action;
	}
	actionsLog.clear();
	for (BaseAction* action : StudioOther.actionsLog)
	{
		actionsLog.push_back(action);
	}
	workout_options.clear();
	for (Workout wrk : StudioOther.workout_options)
	{
		workout_options.push_back(wrk);
	}
	StudioOther.trainers.clear();
	StudioOther.actionsLog.clear();
	StudioOther.workout_options.clear();
	StudioOther.open = false;
	StudioOther._cid = 0;
	return *this;
}

Studio::~Studio()
{
	for (Trainer *tr : trainers)
	{	
			delete tr;	
	}
	trainers.clear();
	for (BaseAction *ba : actionsLog)
	{
		delete ba;
	}
	actionsLog.clear();
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
	return (tid >= 0 && tid < static_cast<int>(trainers.size()) && !trainers[tid]->isOpen());
}

void Studio::start()
{
	std::cout << "The Studio is now open!" << std::endl;
	open = true;
	
	while (open) // Input loop
	{
		std::string sentence;
		getline(cin, sentence);
		std::vector<string> *input = Studio::splitLine(sentence, ' ');
		if ((*input)[0] == "open")
		{
			if (static_cast<int>((*input).size()) <= 2)
			{
				delete input;
				continue;
			}
			vector<Customer *> customers;
			if (not canOpen(std::stoi((*input)[1]), (*input).size() - 2))
			{
				std::vector<Customer *> failed;
				OpenTrainer cantOpen = OpenTrainer(-1, failed);
				cantOpen.trigError("Workout session does not exist or is already open.", sentence);
				actionsLog.push_back(new OpenTrainer(cantOpen));
				delete input;
				continue;
			}
			int tid = std::stoi((*input)[1]);
			std::string inserted = "open " + (*input)[1];
			for (int i = 2; i < static_cast<int>((*input).size()); i++)
			{
				std::vector<string> *currentCustomer = Studio::splitLine((*input)[i], ',');
				if (static_cast<int>(currentCustomer->size()) == 1)
				{
					delete currentCustomer;
					continue;
				}
				std::string name = (*currentCustomer)[0];
				std::string type = (*currentCustomer)[1];
				bool pushed = false;
				if (type == "swt")
				{
					customers.push_back(new SweatyCustomer(name, _cid));
					pushed = true;
				}
				else if (type == "chp")
				{
					customers.push_back(new CheapCustomer(name, _cid));
					pushed = true;
				}
				else if (type == "mcl")
				{
					customers.push_back(new HeavyMuscleCustomer(name, _cid));
					pushed = true;
				}
				else if (type == "fbd")
				{
					customers.push_back(new FullBodyCustomer(name, _cid));
					pushed = true;
				}
				delete currentCustomer;
				if (pushed)
				{
					inserted = inserted + " " + (*input)[i];
					_cid++;
				}
				if (getTrainer(tid)->getCapacity() == static_cast<int>(customers.size()))
				{
					break;
				}
			}
			if (!customers.empty())
			{
				OpenTrainer* currentTrainer = new OpenTrainer(tid, customers);
				currentTrainer->act(*this);
				currentTrainer->setCalledAction(inserted);
				actionsLog.push_back(currentTrainer);
			}
		}
		else if ((*input)[0] == "order")
		{
			if (static_cast<int>((*input).size()) == 1 or (*input)[1].empty())
			{
				delete input;
				continue;
			}
			else
			{
				bool isNum = true;
				for (char ch : (*input)[1])
				{
					if (not std::isdigit(ch))
					{
						cout<<"this ends here"<<endl;
						isNum = false;
						break;
					}
				}
				if (isNum)
				{
					if (std::stoi((*input)[1]) >= getNumOfTrainers())
					{
						delete input;
						continue;
					}
				}
				else 
				{
					delete input;
					continue;
				}
			}
			int id = std::stoi((*input)[1]);
			Order* currentOrder = new Order(id);
			currentOrder->act(*this);
			currentOrder->setCalledAction("order " + (*input)[1]);
			actionsLog.push_back(currentOrder);
		}
		else if ((*input)[0] == "move")
		{
			if (static_cast<int>((*input).size()) == 1 or (*input)[1].empty())
			{
				delete input;
				continue;
			}
			int from = std::stoi((*input)[1]);
			int to = std::stoi((*input)[2]);
			int id = std::stoi((*input)[3]);
			MoveCustomer* currentMove = new MoveCustomer(from, to, id);
			currentMove->act(*this);
			currentMove->setCalledAction("move " + (*input)[1] + " " + (*input)[2] + " " + (*input)[3]);
			actionsLog.push_back(currentMove);
		}
		else if ((*input)[0] == "close")
		{
		if (static_cast<int>((*input).size()) == 1 or (*input)[1].empty() or std::stoi((*input)[1]) >= getNumOfTrainers())
			{
				delete input;
				continue;
			}
			int tid = std::stoi((*input)[1]);;
			Close* closeTrainer = new Close(tid);
			closeTrainer->act(*this);
			closeTrainer->setCalledAction("close " + (*input)[1]);
			actionsLog.push_back(closeTrainer);
		}
		else if ((*input)[0] == "closeall")
		{
			CloseAll* close = new CloseAll();
			close->act(*this);
			close->setCalledAction("closeall");
			actionsLog.push_back(close);
			open = false;
		}
		else if ((*input)[0] == "workout_options")
		{
			PrintWorkoutOptions* prt = new PrintWorkoutOptions();
			prt->act(*this);
			prt->setCalledAction("workout_options");
			actionsLog.push_back(prt);
		}
		else if ((*input)[0] == "status")
		{
		if (static_cast<int>((*input).size()) == 1 or (*input)[1].empty() or std::stoi((*input)[1]) >= getNumOfTrainers())
			{
				delete input;
				continue;
			}
			int tid = std::stoi((*input)[1]);
			PrintTrainerStatus* prt = new PrintTrainerStatus(tid);
			prt->act(*this);
			prt->setCalledAction("status " + (*input)[1]);
			actionsLog.push_back(prt);
		}
		else if ((*input)[0] == "log")
		{
			PrintActionsLog* prt = new PrintActionsLog();
			prt->act(*this);
			prt->setCalledAction("log");
			actionsLog.push_back(prt);
		}
		else if ((*input)[0] == "backup")
		{
			BackupStudio* bck = new BackupStudio();
			bck->setCalledAction("backup");
			actionsLog.push_back(bck);
			bck->act(*this);
		}
		else if ((*input)[0] == "restore")
		{
			RestoreStudio* rst = new RestoreStudio();
			rst->act(*this);
			rst->setCalledAction("restore");
			actionsLog.push_back(rst);
		}
	delete input;
	}
}

