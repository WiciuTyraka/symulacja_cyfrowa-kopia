#include "Table.h"
#include "SimulationObject.h"


Table::Table(const int chair_number)
	:chair_number_(chair_number)
{
	this->current_clients_ = nullptr;
	event_type_ = "table";
}

Group* Table::GetCurrentClients() const
{
	return current_clients_;
}


void Table::SetCurrentClients(Group* wsk)
{
	current_clients_ = wsk;
}

int Table::GetTime()
{
	return time_;
}

void Table::SetTime(int t)
{
	time_ = t;
}

int Table::GetChairNumber() const
{
	return chair_number_;
}


std::string Table::GetEventType()
{
	return event_type_;
}


