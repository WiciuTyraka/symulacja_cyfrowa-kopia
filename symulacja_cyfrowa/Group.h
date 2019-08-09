#pragma once
#include "SimulationObject.h"

class Restaurant;

class Group
	: public SimulationObjcet
{
	const int group_id_;
	int clients_num_;		// number of clients in a group
	bool clients_reference_;
	Restaurant* restaurant_;
	int average_time_;

public:
	Group(const int, Restaurant* restaurant);

	bool GetClientsReference() const;
	int GetGroupId() const;
	int GetNumberOfClients() const;
	int GetClientsNumber() const;

	int GetTime() override;
	void SetTime(int t);

	int GetAverageTime();
	void SetAverageTime(int);

	void Execute(int t) override;
	

};

