#include <iostream>
#include "Restaurant.h"
#include "Manager.h"
#include "SimulationObject.h"
#include <list>
#include <fstream>

using namespace std;

int time_update(void);												//funkcja do aktualizacji casu systemu
void show_list();													// wyswietla liste eventow
bool cmp(SimulationObjcet* w1, SimulationObjcet* w2);				//funkcja do sortowania listy

enum mode
{
	step,
	continuous
};
auto choice = 0;
auto seed = 0;
auto event_trig = true;
auto time = 0;																	// aktualny czas
SimulationObjcet* current_event = nullptr;										// aktualne zdarzenie
Restaurant restaurant(7, 4, 10, 4, 4, 14, rand() % 6 * (11000) + 6 * 10000);			//	const int waiter_num, const int table_2, const int table_3, const int table_4, const int cash_num,const int buffet_spot
Manager* manager = new Manager(30, &restaurant);



int main()
{
		fstream file;

		cout << "wybierz tryb: " << endl << "1. Ciagly" << endl << "2. krokowy" << endl;
		cin >> choice;
		mode mode_ = continuous;
		if (choice == 2) mode_ = step;
		else cout << "tryb bedzie ciagly" << endl;
		cout << "wybierz ziarno (liczba od 1 do 10): "<<endl;
		cin >> seed;
		restaurant.SetSeed(seed);
		restaurant.SetStartTime(4500);							//ustawienie fazy poczatkwoej


		Group * group = new Group(0, &restaurant);				//zaplanowanie pojawienia sie pierwszego klienta
		group->SetTime(10);
		restaurant.lista.push_back(group);



		while (time < 200000)
		{
			event_trig = true;
			time = time_update();													//aktualizacja czasu systemu
	

			// ------------------------------ zdarzenie czasowe ----------------------------------------
			current_event->Execute(time);
			if (mode_ == step) system("PAUSE");

			while (event_trig == true)
			{
				event_trig = false;

				// *****************   zajecie miejsca przy stole ****************************

				Table * table = restaurant.table_check();
				if (!restaurant.table_queue_.empty() && table != nullptr && manager->GetCurrentClients() == nullptr)		//czy kolejka jest nie pusta i jest stolik zdolny pomiescic grupe i manager jest wolny
				{
					manager->ConditionalEvent(table, time);
					if (mode_ == step) system("PAUSE");
					event_trig = true;
				}

				//**************** zajecie miejsca przy bufecie ****************************
				if (!restaurant.buffet_queue_.empty() && restaurant.buffet_queue_[0]->GetNumberOfClients() <= restaurant.GetNumberOfBuffetSpots())			//czy kolejka do bufetu nie jest pusta i czy jest wystarczajaco miejsc przy bufecie
				{
					Buffet* buffet = new Buffet(&restaurant);
					buffet->ConditionalEvent(time);
					if (mode_ == step) system("PAUSE");
					event_trig = true;
				}

				//****************  Rozpoczecie obsługi przez kelnera *************************

				Waiter* waiter = restaurant.waiter_check();
				if (!restaurant.serving_queue_.empty() && waiter != nullptr)										//czy ktos oczekuje na jedzenie i czy jest wolny kelner
				{
					waiter->ConditionalEvent(time);
					if (mode_ == step) system("PAUSE");
					event_trig = true;

				}

				//************ Rozpoczęcie obslugi przez kasjera ***************************

				Cash* cash = restaurant.cash_check();
				if (!restaurant.cashier_queue_.empty() && cash != nullptr)											//czy ktos stoji w kolejce do kasy i czy sa wolni kasjerzy 
				{
					cash->ConditionalEvent(time);
					if (mode_ == step) system("PAUSE");
					event_trig = true;

				}
			}
		}

		file.open("number_of_customers.txt", ios::out | ios::trunc);
		//zapis do pliku tekstowego ilosci osob w systemie w celu wyznaczenia fazy poczatkowej
		for (unsigned int i = 0; i < restaurant.number_of_customers_.size(); i++)
		{
			if (file.good())	file << restaurant.number_of_customers_.at(i) << endl;
		}
		file.close();


		file.open("system_time_.txt", ios::out | ios::trunc);
		//zapis do pliku tekstowego aktualnego czasu systemu
		for (unsigned int i = 0; i < restaurant.system_time_.size(); i++)
		{
			if (file.good())	file << restaurant.system_time_.at(i) << endl;
		}
		file.close();

		double buffet_sum = 0;
		double tables_sum = 0;
		double cash_sum = 0;
		double table_time_sum = 0;
		double waiter_time_sum = 0;

		file.open("average_queue_tables.txt", ios::out | ios::trunc);
		//zapis do pliku tekstowego ilosci osob w systemie w celu wyznaczenia fazy poczatkowej
		for (unsigned int i = 0; i < restaurant.average_queue_tables.size(); i++)
		{
			if (file.good())	file << restaurant.average_queue_tables.at(i) << endl;
			tables_sum = tables_sum + restaurant.average_queue_tables.at(i);
		}
		file.close();


		file.open("average_queue_buffet_.txt", ios::out | ios::trunc);
		//zapis do pliku tekstowego aktualnego czasu systemu
		for (unsigned int i = 0; i < restaurant.average_queue_buffet.size(); i++)
		{
			if (file.good())	file << restaurant.average_queue_buffet.at(i) << endl;
			buffet_sum = buffet_sum + restaurant.average_queue_buffet.at(i);
		}
		file.close();

		file.open("average_queue_cash.txt", ios::out | ios::trunc);
		//zapis do pliku tekstowego aktualnego czasu systemu
		for (unsigned int i = 0; i < restaurant.average_queue_cashiers.size(); i++)
		{
			if (file.good())	file << restaurant.average_queue_cashiers.at(i) << endl;
			cash_sum = cash_sum + restaurant.average_queue_cashiers.at(i);
		}
		file.close();
		file.open("average_table_time_.txt", ios::out | ios::trunc);
		//zapis do pliku tekstowego aktualnego czasu systemu
		for (unsigned int i = 0; i < restaurant.average_time_for_table.size(); i++)
		{
			if (file.good())	file << restaurant.average_time_for_table.at(i) << endl;
			table_time_sum = table_time_sum + restaurant.average_time_for_table.at(i);
		}
		file.close();

		file.open("average_waiter_time.txt", ios::out | ios::trunc);
		//zapis do pliku tekstowego aktualnego czasu systemu
		for (unsigned int i = 0; i < restaurant.average_time_for_waiter.size(); i++)
		{
			if (file.good())	file << restaurant.average_time_for_waiter.at(i) << endl;
			waiter_time_sum = waiter_time_sum + restaurant.average_time_for_waiter.at(i);
		}
		file.close();



		cout << "-------------WYNIKI SYMULACJI-----------------" << endl;
		cout << "srednia ilosc klientow w kolejce do stolow: " << tables_sum / restaurant.average_queue_tables.size() << endl;
		cout << "srednia ilosc klientow w kolejce do bufetu: " << buffet_sum / restaurant.average_queue_buffet.size() << endl;
		cout << "srednia ilosc klientow w kolejce do kasy: " << cash_sum / restaurant.average_queue_cashiers.size() << endl;
		cout << "sredni czas oczekiwania na stol: " << table_time_sum / restaurant.average_time_for_table.size() << endl;
		cout << "sredni czas oczekiwania na kelnera: " << waiter_time_sum / restaurant.average_time_for_waiter.size() << endl;
		return 0;
	}


int time_update()
{
	//show_list();
	restaurant.lista.sort(cmp);
	list<SimulationObjcet*>::iterator iter;
	iter = restaurant.lista.begin();
	current_event = *iter;
	restaurant.lista.pop_front();
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
	for (it = restaurant.lista.begin(); it != restaurant.lista.end(); ++it)
	{
		wsk = *it;
		cout << " time: " << wsk->GetTime() << " event_type: " << endl;
	}
}





