#pragma once
#include "Group.h"
#include "SimulationObject.h"


class Cash
	: public SimulationObjcet
{
	Group* current_clients_;
public:
	Cash();
	Group* GetCurrentClients() const; 
	void SetCurrentClients(Group* wsk);
	int GetTime() override;
	void SetTime(int t);
	std::string GetEventType() override;
};
