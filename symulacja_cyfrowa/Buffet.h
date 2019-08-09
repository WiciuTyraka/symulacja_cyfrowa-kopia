#pragma once
#include <vector>
#include "Group.h"
#include "SimulationObject.h"


class Buffet
	: public SimulationObjcet
{
	Group* current_clients_;
	Restaurant* restaurant_;

public:

	Buffet(Restaurant* restaurant);

	Group* GetCurrentClients(void) const;
	void SetCurrentClients(Group* wsk);

	int GetTime() override;
	void SetTime(int t);

	void ConditionalEvent(int t);

	void Execute(int t) override;

};

