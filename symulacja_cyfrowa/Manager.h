#pragma once
#include "Group.h"
#include "SimulationObject.h"
#include "Table.h"

class Manager
	: public SimulationObjcet
{
	const int service_time_;
	Group* current_clients_;
	Table* table_destination_;
	//Group* current_clients_;
public:
	explicit  Manager(const int);
	Group* GetCurrentClients() const;
	void SetCurrentClients(Group* wsk);
	Table* GetTableDestination() const;
	void SetTableDestination(Table* wsk);
	int GetTime() override;
	void SetTime(int t);
	std::string GetEventType() override;
};

