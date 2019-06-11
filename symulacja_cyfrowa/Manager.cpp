#include "Manager.h"
#include "SimulationObject.h"


Manager::Manager(const int service_time)
	:service_time_(service_time)
{
	this->current_clients_ = nullptr;
	this->table_destination_ = nullptr;
	event_type_ = "manager";
}

Group* Manager::GetCurrentClients() const
{
	return current_clients_;
}


void Manager::SetCurrentClients(Group* wsk)
{
	current_clients_ = wsk;
}

Table* Manager::GetTableDestination() const
{
	return table_destination_;
}

void Manager::SetTableDestination(Table* wsk)
{
	table_destination_ = wsk;
}

int Manager::GetTime()
{
	return time_;
}

void Manager::SetTime(int t)
{
	time_ = t;
}

std::string Manager::GetEventType()
{
	return event_type_;
}



