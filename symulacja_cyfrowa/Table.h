#pragma once
#include "Group.h"
#include "SimulationObject.h"

class Table
	: public SimulationObjcet
{
	const int chair_number_;
	Group* current_clients_;
public:
	explicit 	Table(const int);
	Group* GetCurrentClients(void) const;
	void SetCurrentClients(Group* wsk);
	int GetTime() override;
	void SetTime(int t);
	int GetChairNumber() const;
	std::string GetEventType() override;
};
