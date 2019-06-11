#include <iostream>
#include "Restaurant.h"
#include "Manager.h"
#include "SimulationObject.h"
#include <list>
using namespace std;

int time_update(void);											//funkcja do aktualizacji casu systemu
void show_list();												// wyswietla liste eventow
bool cmp(SimulationObjcet* w1, SimulationObjcet* w2);			//funkcja do sortowania listy
Table* table_check();								// funkcja służąca do sprawdzenia czy grupa zmiesci sie do jakiegos stolika
Waiter* waiter_check(void);
Cash* cash_check(void);

auto time = 0;													// aktualny czas
SimulationObjcet* current_event = nullptr;						// aktualne zdarzenie
Restaurant restaurant(7, 4, 10, 4, 4, 14);						//	const int waiter_num, const int table_2, const int table_3, const int table_4, const int cash_num,const int buffet_spot
Manager* manager = new Manager(30);

list<SimulationObjcet*> lista;									//utworzenie listy zdarzen

int main()
{
	// -------- do wyjebania -----
	auto id_number = 0;
	const auto num_of_person_= 2;
	//---------------------------


	Group *group = new Group(id_number++, num_of_person_);			//zaplanowanie pojawienia sie pierwszego klienta
	group -> SetTime(10);
	lista.push_back(group);



	while (time < 50000)
	{
		time = time_update();								//aktualizacja czasu systemu
		
		//--------------------   czy pojawiła sie nowa grupa?  ---------------------------------------
		if(current_event->GetEventType()=="group")					
		{
			restaurant.table_queue_.push_back(group);				//ustaw klienta w kolejce
			cout << "pojawila sie grupa o ID: " << group->GetGroupId() << " czas systemu: " << time << endl;
			// losowanie czasu pojawenia sie i liczebnosci
			group = new Group(id_number++, num_of_person_);			//zaplanuj kolejnego klienta
			group->SetTime(time+70);
			lista.push_back(group);
		}

		//--------------------   czy manager skonczyl obsługe?  ---------------------------------------
		if(current_event->GetEventType()=="manager")              
		{
			cout << "manager skonczyl obsluge grupy o ID: " << manager->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << endl;

			restaurant.serving_queue_.push_back(manager->GetTableDestination());					// ustawienie stolow w kolejce oczekujacych na kelnerow
			manager->SetCurrentClients(nullptr);												 //zwolnij managera
			manager->SetTableDestination(nullptr);

		}
		//--------------------   czy kelner skonczyl obsługe?  ---------------------------------------
		if(current_event->GetEventType() == "waiter")		      
		{
			Waiter* current_waiter = dynamic_cast<Waiter*>( current_event);
			cout << "kelner skonczyl obslugiwac grupe o  ID: " << current_waiter->GetCurrentTable()->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << endl;
			//losowanie czasu konsumpcji
			Table* table_ = current_waiter->GetCurrentTable();
			table_->SetTime(time+60);
			lista.push_back(table_);									//zaplanuj koniec konsumpcji

			current_waiter->SetCurrentTable(nullptr);			//zwolnij kelnera
		}

		//--------------------   czy grupa skonczyla posiłek?  ---------------------------------------
		if(current_event->GetEventType() == "table")
		{
			Table* current_table = dynamic_cast<Table*>( current_event);
			cout << "posilek skonczyla grupa o  ID: " << current_table->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << endl;
			Group* gr = current_table->GetCurrentClients();
			restaurant.cashier_queue_.push_back(gr);			//ustaw klientow w kolejce do kasy

			current_table->SetCurrentClients(nullptr);		//zwolnij stolik
		}

		//------------------------------- czy grupa zaplacila -----------------------------------
		if(current_event->GetEventType()=="cash")
		{
			Cash* current_cash = dynamic_cast<Cash*>(current_event);
			cout << "system opuszcza grupa o  ID: " << current_cash->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << endl;
			Group* gr = current_cash->GetCurrentClients();
			
			delete gr;

			current_cash->SetCurrentClients(nullptr);		//zwolnij kasjera
		}

		// *****************   zajecie miejsca przy stole ****************************

		Table* table = table_check();
		if(!restaurant.table_queue_.empty() && table!=nullptr && manager->GetCurrentClients() == nullptr  )		//czy kolejka jest nie pusta i jest stolik zdolny pomiescic grupe i manager jest wolny
		{
			cout << "do stolika zostanie przydzielona grupa o  ID: " << restaurant.table_queue_[0]->GetGroupId() << " czas systemu: " << time <<" stolik jest osobwy: "<<table->GetChairNumber()<< endl;
			manager->SetCurrentClients(restaurant.table_queue_[0]);			//manager pobiera ludzi z kolejki
			manager->SetTableDestination(table);
			table->SetCurrentClients(manager->GetCurrentClients());		//przydziel klientom stolik
			restaurant.table_queue_.erase(restaurant.table_queue_.begin());								//usun klientow z kolejki

			manager->SetTime(time+10);
			lista.push_back(manager);										// zaplanuj koniec obsługi managera

		}

		//****************  Rozpoczecie obsługi przez kelnera *************************

		Waiter* waiter = waiter_check();
		if(!restaurant.serving_queue_.empty() && waiter != nullptr )   //czy ktos oczekuje na jedzenie i czy jest wolny kelner
		{
			waiter->SetCurrentTable(restaurant.serving_queue_[0]);				//przydziel kelnerowi najdluzej oczekujacy stol
			cout << "kelner zacznie obslugiwac grupe o  ID: " << waiter->GetCurrentTable()->GetCurrentClients()->GetGroupId() << " czas systemu: " << time << endl;
			restaurant.serving_queue_.erase(restaurant.serving_queue_.begin());								//usun stol z kolejki oczekujacych na obsluge
			//losowanie czasu obslugi
			waiter->SetTime(time+100);
			lista.push_back(waiter);											//zaplanuj koniec obslugi kelnera
		}

		//************ Rozpoczęcie obslugi przez kasjera ***************************

		Cash* cash = cash_check();
		if(!restaurant.cashier_queue_.empty() && cash != nullptr)				//czy ktos stoji w kolejce do kasy i czy sa wolni kasjerzy 
		{
			cout << "kasjer zaczya obsluge stolu  o ID: " << restaurant.cashier_queue_[0]->GetGroupId() << " czas systemu: " << time << endl;
			cash->SetCurrentClients(restaurant.cashier_queue_[0]);				//przydziel grupe do wolnego kasjera
			restaurant.cashier_queue_.erase(restaurant.cashier_queue_.begin());								//usun grupe z kolejki do kasy
			//losowanie czasu obslugi
			cash->SetTime(time+20);
			lista.push_back(cash);												// zaplanuj koniec obslugi przez kasjera
		}
	}
	
	
	return 0;
}

int time_update()
{
	//show_list();
	lista.sort(cmp);
	list<SimulationObjcet*>::iterator iter;
	iter = lista.begin();
	current_event = *iter;
	lista.pop_front();
	return current_event->GetTime() ;
		
}

bool cmp(SimulationObjcet* w1, SimulationObjcet* w2)
{
	return  w2->GetTime() > w1->GetTime();
}

void show_list()
{
	list<SimulationObjcet*>::iterator it;
	SimulationObjcet* wsk;
	for (it = lista.begin(); it != lista.end(); ++it)
	{
		wsk = *it;
	
		cout << " time: " << wsk->GetTime() << " event_type: " << wsk->GetEventType() << endl;

	}
}

Table* table_check()
{
	if (!restaurant.table_queue_.empty())
	{
		const int num_of_person = restaurant.table_queue_[0]->GetClientsNumber();

		for (auto i : restaurant.tables_2_)
			if (i->GetCurrentClients() == nullptr && num_of_person == 2)	return i;

		for (auto i : restaurant.tables_3_)
			if (i->GetCurrentClients() == nullptr && (num_of_person == 3 || num_of_person == 2))	return i;

		for (auto i : restaurant.tables_4_)
			if (i->GetCurrentClients() == nullptr && (num_of_person == 4 || num_of_person == 3 || num_of_person == 2))	return i;
	}
	return nullptr;
}

Waiter* waiter_check()
{
	for(auto i : restaurant.waiters_)
	{
		if (i->GetCurrentTable() == nullptr)	return i;
	}

	return nullptr;
}

Cash* cash_check()
{

	for(auto i :restaurant.cash_)
	{
		if (i->GetCurrentClients() == nullptr)		return i;
	}

	return  nullptr;
}



