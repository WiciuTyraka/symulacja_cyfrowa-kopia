#include "Buffet.h"
#include "SimulationObject.h"

Buffet::Buffet()
{
	this->current_clients_ = nullptr;
	event_type_ = "buffet";
}

int Buffet::GetTime()
{
	return time_;
}

void Buffet::SetTime(int t)
{
	time_ = t;
}
std::string Buffet::GetEventType()
{
	return event_type_;
}




