#include "Restaurant.h"
#include <cstdio>
#include <vector>

Restaurant::Restaurant(const int waiter_num, const int table_2, const int table_3, const int table_4, const int cash_num,const int buffet_spot)
	: waiter_number_(waiter_num),
	  two_chair_tables_(table_2),
	  three_chair_tables_(table_3),
	  four_chair_tables_(table_4),
	  cash_number_(cash_num),
	  buffet_spot_(buffet_spot)
//manager_(wilku)

{
	//this->waiters_ = std::vector<Waiter*>(waiter_number_, new Waiter());
	//this->cash_ = std::vector<Cash*>(cash_number_, new Cash());
	//this->buffet_ = std::vector<Buffet*>(buffet_spot_, new Buffet());
	//this->tables_2_ = std::vector<Table*>(two_chair_tables_, new Table(2));
	//this->tables_3_ = std::vector<Table*>(three_chair_tables_, new Table(3));
	//this->tables_4_ = std::vector<Table*>(four_chair_tables_, new Table(4));

	this->table_queue_ = std::vector<Group*>();
	this->cashier_queue_ = std::vector<Group*>();
	this->buffet_queue_ = std::vector<Group*>();
	this->serving_queue_= std::vector<Table*>();

	for (auto i = 0; i < waiter_number_; i++)
	{
		waiters_.push_back(new Waiter());
	}

	for(auto i=0;i<cash_number_;i++)
	{
		cash_.push_back(new Cash());
	}

	for (auto i = 0; i < buffet_spot_; i++)
	{
		buffet_.push_back(new Buffet());
	}

	for (auto i = 0; i < two_chair_tables_; i++)
	{
		tables_2_.push_back(new Table(2));
	}

	for (auto i = 0; i < three_chair_tables_; i++)
	{
		tables_3_.push_back(new Table(3));
	}

	for (auto i = 0; i < four_chair_tables_; i++)
	{
		tables_4_.push_back(new Table(4));
	}

}
