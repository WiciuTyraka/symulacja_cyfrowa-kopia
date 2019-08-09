#include "Manager.h"
#include "SimulationObject.h"
#include "Restaurant.h"


Manager::Manager(const int service_time, Restaurant* restaurant)
	:service_time_(service_time),
	restaurant_(restaurant)
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

void Manager::ConditionalEvent(Table* table,int time)
{
	std::cout << "do stolika zostanie przydzielona grupa o  ID: " << restaurant_->table_queue_[0]->GetGroupId() << " czas systemu: " << time << " stolik jest osobwy: " << table->GetChairNumber() << std::endl;

	this->SetCurrentClients(restaurant_->table_queue_[0]);											//manager pobiera ludzi z kolejki
	this->SetTableDestination(table);																//manager musi wiedziec jaki jest docelowy stolik
	table->SetCurrentClients(this->GetCurrentClients());											//przydziel klientom stolik
	restaurant_->table_queue_.erase(restaurant_->table_queue_.begin());						//usun klientow z kolejki

	this->SetTime(time + this->service_time_);													//ustaw czas
	restaurant_->lista.push_back(this);

	if (time > restaurant_->GetStartTime())
	{
		restaurant_->average_queue_tables.push_back(restaurant_->table_queue_.size());					//zapis stanu kolejki w celu anallizy wyników

		restaurant_->average_time_for_table.push_back(time - this->GetCurrentClients()->GetAverageTime());
		this->GetCurrentClients()->SetAverageTime(time + this->service_time_);
	}
}



void Manager::Execute(const int time)		//--------------------   czy manager skonczyl obs³uge?  ---------------------------------------
{
	std::cout << "manager skonczyl obsluge grupy o ID: " << this->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << std::endl;

	restaurant_->serving_queue_.push_back(this->GetTableDestination());							// ustawienie stolow w kolejce oczekujacych na kelnerow
	this->SetCurrentClients(nullptr);															 //zwolnij managera
	this->SetTableDestination(nullptr);
}



