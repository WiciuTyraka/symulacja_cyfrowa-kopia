#pragma once
#include "Group.h"
#include "SimulationObject.h"


class Cash
	: public SimulationObjcet
{
	Group* current_clients_;
	Restaurant* restaurant_;
public:
	Cash(Restaurant* restaurant);

	Group* GetCurrentClients() const; 
	void SetCurrentClients(Group* wsk);

	int GetTime() override;
	void SetTime(int t);

	void ConditionalEvent( int t);

	void Execute(int t) override;
};
