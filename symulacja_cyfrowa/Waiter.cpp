#include "Waiter.h"
#include "SimulationObject.h"


Waiter::Waiter()
{
	this->current_table_= nullptr;
	event_type_ = "waiter";
}

Table* Waiter::GetCurrentTable() const
{
	return current_table_;
}



void Waiter::SetCurrentTable(Table* wsk)
{
	current_table_ = wsk;
}

int Waiter::GetTime()
{
	return time_;
}

void Waiter::SetTime(int t)
{
	time_ = t;
}
std::string Waiter::GetEventType()
{
	return event_type_;
}

