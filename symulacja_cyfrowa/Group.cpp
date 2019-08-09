#include "Group.h"
#include "SimulationObject.h"
#include <ctime>
#include  "Restaurant.h"


Group::Group(const int group_id,Restaurant* restaurant)
	: group_id_(group_id),
	  restaurant_(restaurant)
{
	event_type_ = "group";
	const int probability = rand()%100;
	if (probability >= 0 && probability < 11) clients_num_ = 1;
	else if (probability >= 11 && probability < 44) clients_num_ = 2;
	else if (probability >= 44 && probability < 77) clients_num_ = 3;
	else clients_num_ = 4;
	clients_reference_ = rand() % 2;
}

bool Group::GetClientsReference() const
{
	return  clients_reference_;
}


int Group::GetGroupId() const
{
	return group_id_;
}

int Group::GetNumberOfClients()	const
{
	return clients_num_;

}

int Group::GetClientsNumber() const
{
	return clients_num_;
}


int Group::GetTime()
{
	return time_;
}

void Group::SetTime(int t)
{
	time_ = t;
}

int Group::GetAverageTime()
{
	return average_time_;
}

void Group::SetAverageTime(int t)
{
	average_time_ = t;
}


void Group::Execute(int time)			//--------------------   czy pojawi³a sie nowa grupa?  ---------------------------------------
{
	if (this->GetClientsReference() == false)	restaurant_->table_queue_.push_back(this);			//ustaw klienta w kolejce do restauracji
	else restaurant_->buffet_queue_.push_back(this);													//ustaw klienta w kolejce do bufetu

	std::cout << "pojawila sie grupa o ID: " << this->GetGroupId() << " czas systemu: " << time << std::endl;

	// losowanie czasu pojawenia sie grupy
	Group *group = new Group(this->GetGroupId()+1,restaurant_);			//zaplanuj kolejnego klienta
	group->SetTime(time + restaurant_->NewGroupAppear());
	restaurant_->lista.push_back(group);

	//wartosci potrzebne do wyznaczenia fazy pocz¹tkowej
	restaurant_->customers = restaurant_->customers + group->GetClientsNumber();
	restaurant_->number_of_customers_.push_back(restaurant_->customers);
	restaurant_->system_time_.push_back(time);

	//wyznaczanie sredniej dlugosci oczekiwania w kolejce
	if (time >= restaurant_->GetStartTime())	this->SetAverageTime(time);


}






