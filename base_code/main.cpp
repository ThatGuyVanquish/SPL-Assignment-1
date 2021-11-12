#include "Studio.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;

int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage: studio <config_path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
    Studio studio(configurationFile);
    studio.start();
    int id = 0;
    while (true) //input loop
    {
        //receive input and separate into input vector by spaces
        /*
        if (input[0] == "open") 
        {
            vector<Customer*> customers;
            for(int i = 2; i < input.size(); i++)
            {
                std::string name;
                std::string type;
                std::string gotLine;
                while (getline(input[i], gotLine, ',')
                {
                    if (not name)
                    {
                        name(&gotLine);
                    }
                    else
                    {
                        type(&gotLine);
                    }
                }
                if (type == "swt")
                {
                    customers.push_back(*(SweatyCustomer::SweatyCustomer(name, id)));
                    id++;
                }
                if (type == "chp")
                {
                    customers.push_back(*(CheapCustomer::CheapCustomer(name, id)));
                    id++;
                }
                if (type == "mcl")
                {
                    customers.push_back(*(HeavyMuscleCustomer::HeavyMuscleCustomer(name, id)));
                    id++;
                }
                if (type == "fbc")
                {
                    customers.push_back(*(FullBodyCustomer::FullBodyCustomer(name, id)));
                    id++;
                }
                customers.push_back(*(Customer(input[i], )))
            }
            OpenTrainer currentTrainer = OpenTrainer::OpenTrainer(input[1], customers);
            currentTrainer.act(studio);
        }
        if (input[0] == "order")
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
            we gotta perform checks to see if :
            origin trainer exists and his session is open
            destination trainer exists and is open
            the customer with said id is in origin trainers session, w
        }
        */ 
    }

    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}