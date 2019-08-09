#include "Waiter.h"
#include "SimulationObject.h"
#include "Restaurant.h"
#include <ctime>



Waiter::Waiter(Restaurant* restaurant)
	:restaurant_(restaurant)
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

void Waiter::ConditionalEvent(int time)
{
	this->SetCurrentTable(restaurant_->serving_queue_[0]);											//przydziel kelnerowi najdluzej oczekujacy stol
	std::cout << "kelner zacznie obslugiwac grupe o  ID: " << this->GetCurrentTable()->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << std::endl;

	restaurant_->serving_queue_.erase(restaurant_->serving_queue_.begin());						//usun stol z kolejki oczekujacych na obsluge
	this->SetTime(time + restaurant_->ServiceTime());													//losowanie czasu obslugi
	restaurant_->lista.push_back(this);																	//zaplanuj koniec obslugi kelnera


	if (time > restaurant_->GetStartTime())	restaurant_->average_time_for_waiter.push_back(time - this->GetCurrentTable()->GetCurrentClients()->GetAverageTime());
}

void Waiter::Execute(int time)	//--------------------   czy kelner skonczyl obs³uge?  ---------------------------------------
{
	//Waiter* current_waiter = dynamic_cast<Waiter*>(this);
	std::cout << "kelner skonczyl obslugiwac grupe o  ID: " << this->GetCurrentTable()->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << std::endl;

	this->GetCurrentTable()->SetTime(time + restaurant_->ConsumptionTime());		//losowanie czasu
	restaurant_->lista.push_back(this->GetCurrentTable());							//zaplanuj koniec konsumpcji
	this->SetCurrentTable(nullptr);												//zwolnij kelnera
}

