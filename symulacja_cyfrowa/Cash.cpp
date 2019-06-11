#include "Cash.h"
#include "SimulationObject.h"

Cash::Cash()
{
	this->current_clients_ = nullptr;
	event_type_ = "cash";
}

Group* Cash::GetCurrentClients() const
{
	return  current_clients_;
}



void Cash::SetCurrentClients(Group* wsk)
{
	current_clients_ = wsk;
}

int Cash::GetTime()
{
	return time_;
}

void Cash::SetTime(int t)
{
	time_ = t;
}
std::string Cash::GetEventType()
{
	return event_type_;
}


