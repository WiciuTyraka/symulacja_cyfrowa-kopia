#pragma once
#include "Group.h"
#include "SimulationObject.h"

class Table
	: public SimulationObjcet
{
	const int chair_number_;
	Group* current_clients_;
	 Restaurant* restaurant_;
public:
	explicit Table(const int, Restaurant* restaurant);

	Group* GetCurrentClients(void) const;
	void SetCurrentClients(Group* wsk);

	int GetTime() override;
	void SetTime(int t);

	int GetChairNumber() const;

	void Execute(int t) override;

};
