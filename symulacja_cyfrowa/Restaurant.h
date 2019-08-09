#pragma once
#include "Waiter.h"
#include <vector>
#include "Table.h"
#include "Cash.h"
#include "Buffet.h"
#include <list>
#include <random>

using  namespace std;

class Restaurant
{

	const int waiter_number_;
	const int two_chair_tables_;
	const int three_chair_tables_;
	const int four_chair_tables_;
	const int cash_number_;
	int buffet_spot_;
	const int seed_;
	int start_collecting_data;
public:

	explicit  Restaurant(const int, const int, const int, const int, const int, const int, const int);

	vector<Waiter*> waiters_;
	vector<Cash*> cash_;
	vector<Table*> tables_2_;
	vector<Table*> tables_3_;
	vector<Table*> tables_4_;

	vector<Group*> table_queue_;
	vector<Group*> cashier_queue_;
	vector<Group*> buffet_queue_;
	vector<Table*> serving_queue_;

	std::list<SimulationObjcet*> lista;								//utworzenie listy zdarzen


	// ---------------------------------------------- generatory
	void SetSeed(int);
	default_random_engine generator_;
	normal_distribution<double> normal_dist_new_group_ = normal_distribution<double>(320, 35);
	normal_distribution <double> normal_dist_buffet_ = normal_distribution<double>(3200, 100);			//nie zmieniac 
	exponential_distribution<double> exponential_dist_drinks_ = exponential_distribution<double>(1 / 1650.0);
	exponential_distribution<double> exponential_dist_food_ = exponential_distribution<double>(1 / 2750.0);
	exponential_distribution<double> exponential_dist_eat_ = exponential_distribution<double>(1 / 1900.0);		//nie zmieniac
	exponential_distribution<double> exponential_dist_cashier_ = exponential_distribution<double>(1 / 1000.0);

	//-------------------------------------------kontenery do zbierania danych
	vector <int> number_of_customers_;			//liczba klientow w systemie - do wyznaczenia fazy poczatkowej
	int customers;								// aktualna liczba klientow w systemie
	vector <int> system_time_;					//czas pojawienia sie klienta - do wyznaczenia fazy poczatkowej
	vector <int> average_queue_tables;
	vector <int> average_queue_cashiers;
	vector <int> average_queue_buffet;
	vector <int> average_time_for_table;
	vector <int> average_time_for_waiter;
	int GetStartTime(void);						//funkcje do usawienia fazy poczatkowej
	void SetStartTime(int x);
	


	int GetNumberOfBuffetSpots() const;			//funkcja zwracajaca ilosc wolnych miejsc przy bufecie
	void TakeBuffetSpots(int);					//funkcja sluzaca do zajmowania miejsc przy bufecie
	void FreeBuffetSpots(int);					//funkcja sluzaca do zwalniania miejsc przy bufecie

	Table* table_check() const;					// funkcja s³u¿¹ca do sprawdzenia czy grupa zmiesci sie do jakiegos stolika
	Waiter* waiter_check(void) const;			//funkcja do szukania wolnego klenera	
	Cash* cash_check(void) const;				//funkcja do szukania wolnego kasjera


	//--------------------funkcje zwracaj¹ce wartosci losowe dla odpowiednich zdarzen
	int ServiceTime(void);
	int ConsumptionTime(void);
	int CashierTime(void);
	int BuffetTime(void);
	int NewGroupAppear(void);



};

