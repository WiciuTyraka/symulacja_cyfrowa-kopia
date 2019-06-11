#pragma once
#include "Group.h"
#include "SimulationObject.h"
#include "Table.h"

class Waiter
	: public SimulationObjcet
{
	Table* current_table_;
public:
	Waiter();
	Table* GetCurrentTable() const;
	void SetCurrentTable(Table* wsk);

	int GetTime() override;
	void SetTime(int t);

	std::string GetEventType() override;

	
};

