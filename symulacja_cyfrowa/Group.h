#pragma once
#include "SimulationObject.h"

class Group
	: public SimulationObjcet
{
	const int group_id_;
	const int clients_num_;		// number of clients in a group
	
	bool main_dish_served_;    // information if main dish was served.
	bool drink_served_;		   // information if drink was served.

public:
	Group(const int, const int);

	int GetGroupId() const;
	int GetNumberOfClients() const;
	int GetClientsNumber() const;
	int GetTime() override;
	void SetTime(int t);
	std::string GetEventType() override;
	

};

