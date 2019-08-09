#include "Buffet.h"
#include "SimulationObject.h"
#include  "Restaurant.h"
#include <ctime>

Buffet::Buffet(Restaurant* restaurant)
	:restaurant_(restaurant)
{
	this->current_clients_ = nullptr;
	event_type_ = "buffet";
}

Group* Buffet::GetCurrentClients() const
{
	return current_clients_;
}

void Buffet::SetCurrentClients(Group* wsk)
{
	current_clients_ = wsk;
}

int Buffet::GetTime()
{
	return time_;
}

void Buffet::SetTime(int t)
{
	time_ = t;
}

void Buffet::ConditionalEvent(int time)
{
	restaurant_->TakeBuffetSpots(restaurant_->buffet_queue_[0]->GetClientsNumber());					//pomniejssz liczbe wolnych miejsc przy bufecie o liczbe klientow  wgrupie
	this->SetCurrentClients(restaurant_->buffet_queue_[0]);												//Ustawia wskanizk na grupe klientow na jednym z zajetych miejsc
	this->SetTime(time + restaurant_->BuffetTime());													//losowanko czasu konsumpcji
	restaurant_->lista.push_back(this);																	//zaplanuj koniec konsumpcji

	std::cout << "do bufetu usiadla grupa o ID: " << restaurant_->buffet_queue_[0]->GetGroupId() << " czas systemu: " << time << " przy bufecie zostalo miejsc: " << restaurant_->GetNumberOfBuffetSpots() << std::endl;
	
	restaurant_->buffet_queue_.erase(restaurant_->buffet_queue_.begin());							//usun klientow z kolejki do bufetu
	if (time > restaurant_->GetStartTime())
	{
		restaurant_->average_queue_buffet.push_back(restaurant_->buffet_queue_.size());						//zapisz stan kolejki w celu analizy wyników
	}
}


void Buffet::Execute(int time)				//--------------------   czy grupa przy bufecie skonczyla posi³ek?  ---------------------------------------
{
	//Buffet* current_spot = dynamic_cast<Buffet*>(current_event);

	Group* gr = this->GetCurrentClients();
	restaurant_->cashier_queue_.push_back(gr);													//ustaw klientow  wkolejce do kasy

	restaurant_->FreeBuffetSpots(gr->GetClientsNumber());										//zwolnij miejsca
	std::cout << "-----------------posilek przy bufecie skonczyla grupa o  ID: " << this->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << " wolnych miejsc przy bufecie jest " << restaurant_->GetNumberOfBuffetSpots() << std::endl;

	delete this;
}




