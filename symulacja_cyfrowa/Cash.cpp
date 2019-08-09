#include "Cash.h"
#include "SimulationObject.h"
#include "Restaurant.h"

Cash::Cash(Restaurant* restaurant)
	:restaurant_(restaurant)
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

void Cash::ConditionalEvent(int time)
{
	std::cout << "kasjer zaczya obsluge stolu  o ID: " << restaurant_->cashier_queue_[0]->GetGroupId() << " czas systemu: " << time << std::endl;

	this->SetCurrentClients(restaurant_->cashier_queue_[0]);											//przydziel grupe do wolnego kasjera
	restaurant_->cashier_queue_.erase(restaurant_->cashier_queue_.begin());						//usun grupe z kolejki do kasy
	this->SetTime(time + restaurant_->CashierTime());													//losowanie czasu obslugi
	restaurant_->lista.push_back(this);																	// zaplanuj koniec obslugi przez kasjera

	//srednia kolejka
	if(time>restaurant_->GetStartTime())	restaurant_->average_queue_cashiers.push_back(restaurant_->cashier_queue_.size());
}


void Cash::Execute(int time)					//------------------------------- czy grupa zaplacila -----------------------------------
{
	std::cout << "system opuszcza grupa o  ID: " << this->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << std::endl;

	restaurant_->customers = restaurant_->customers - this->GetCurrentClients()->GetClientsNumber();
	restaurant_->number_of_customers_.push_back(restaurant_->customers);
	restaurant_->system_time_.push_back(time);

	delete this->GetCurrentClients();															//usun grupe z systemu

	this->SetCurrentClients(nullptr);														//zwolnij kasjera
}


