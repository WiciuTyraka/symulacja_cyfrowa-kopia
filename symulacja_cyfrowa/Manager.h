#pragma once
#include "Group.h"
#include "SimulationObject.h"
#include "Table.h"
#include "Restaurant.h"

class Manager
	: public SimulationObjcet
{
	const int service_time_;							//czas obslugi przez managera		
	Group* current_clients_;							//wskaznik na aktualnie obslugiwany stolik
	Table* table_destination_;							//wskaznik na wyznaczony stol	
	Restaurant* restaurant_;								

public:
	explicit  Manager(const int,Restaurant* restaurant);

	Group* GetCurrentClients() const;
	void SetCurrentClients(Group* wsk);

	Table* GetTableDestination() const;
	void SetTableDestination(Table* wsk);

	int GetTime() override;
	void SetTime(int t);

	void ConditionalEvent(Table* table, int t);

	void Execute(int time) override;
};

