#pragma once
#include "Waiter.h"
#include <vector>
#include "Table.h"
#include "Cash.h"
#include "Buffet.h"
#include "Manager.h"

class Restaurant
{
public:
	const int waiter_number_;
	const int two_chair_tables_;
	const int three_chair_tables_;
	const int four_chair_tables_;
	const int cash_number_;
	const int buffet_spot_;

	std::vector<Waiter*> waiters_;
	std::vector<Cash*> cash_;
	std::vector<Buffet*> buffet_;
	std::vector<Table*> tables_2_;
	std::vector<Table*> tables_3_;
	std::vector<Table*> tables_4_;

	std::vector<Group*> table_queue_;
	std::vector<Group*> cashier_queue_;
	std::vector<Group*> buffet_queue_;
	std::vector<Table*> serving_queue_;
	
	//Manager manager_;





	explicit  Restaurant(const int, const int, const int, const int, const int,const int);

};

