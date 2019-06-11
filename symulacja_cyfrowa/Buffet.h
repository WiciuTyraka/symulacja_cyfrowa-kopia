#pragma once
#include <vector>
#include "Group.h"
#include "SimulationObject.h"


class Buffet
	: public SimulationObjcet
{
	Group* current_clients_;

public:

	Buffet();
	int GetTime() override;
	void SetTime(int t);
	std::string GetEventType() override;

};

