#include "Queue.h"
#include "Group.h"


Queue::Queue()
{
	this->clients_queue_ = std::vector<Group*>(1,nullptr);
			
}



