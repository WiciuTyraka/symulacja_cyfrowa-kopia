#include "Group.h"
#include "SimulationObject.h"




Group::Group(const int group_id, const int clients_num)
	: group_id_(group_id),
	clients_num_(clients_num)
{
	this->main_dish_served_ = false;
	this->drink_served_ = false;
	event_type_ = "group";
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

std::string Group::GetEventType()
{
	return event_type_;
}






