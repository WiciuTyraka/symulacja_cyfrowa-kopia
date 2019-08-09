#pragma once
#include "Group.h"
#include "SimulationObject.h"
#include "Table.h"
//#include "Restaurant.h"

class Waiter
	: public SimulationObjcet
{
	Table* current_table_;						//wskaznik na aktualnie obslugiwany stol
	Restaurant* restaurant_;					
public:
	Waiter(Restaurant* restaurant);

	Table* GetCurrentTable() const;
	void SetCurrentTable(Table* wsk);

	int GetTime() override;
	void SetTime(int t);

	void ConditionalEvent( int t);

	void Execute(int t) override;

	
};

