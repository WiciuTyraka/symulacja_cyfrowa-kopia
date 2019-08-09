#include "Table.h"
#include "SimulationObject.h"
#include "Restaurant.h"


Table::Table(const int chair_number, Restaurant* restaurant)
	:chair_number_(chair_number),
	restaurant_(restaurant)
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

void Table::Execute(int time)			//--------------------   czy grupa skonczyla posi³ek?  ---------------------------------------
{
	std::cout << "posilek skonczyla grupa o  ID: " << this->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << std::endl;

	restaurant_->cashier_queue_.push_back(this->GetCurrentClients());						//ustaw klientow w kolejce do kasy

	this->SetCurrentClients(nullptr);													//zwolnij stolik
}


