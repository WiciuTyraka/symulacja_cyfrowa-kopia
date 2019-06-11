#pragma once
#include <string>

class SimulationObjcet
{
protected:
	int time_ = 0;
	std::string event_type_;


public:
	virtual ~SimulationObjcet() = default;
	virtual int GetTime() = 0;
	virtual std::string GetEventType() = 0;

	
};
