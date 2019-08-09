#include "Restaurant.h"
#include <cstdio>
#include <vector>


Restaurant::Restaurant(const int waiter_num, const int table_2, const int table_3, const int table_4, const int cash_num,const int buffet_spot,const int seed)
	: waiter_number_(waiter_num),
	  two_chair_tables_(table_2),
	  three_chair_tables_(table_3),
	  four_chair_tables_(table_4),
	  cash_number_(cash_num),
	  buffet_spot_(buffet_spot),
	  seed_(seed)

{
	//this->waiters_ = std::vector<Waiter*>(waiter_number_, new Waiter());
	//this->cash_ = std::vector<Cash*>(cash_number_, new Cash());
	//this->buffet_ = std::vector<Buffet*>(buffet_spot_, new Buffet());
	//this->tables_2_ = std::vector<Table*>(two_chair_tables_, new Table(2));
	//this->tables_3_ = std::vector<Table*>(three_chair_tables_, new Table(3));
	//this->tables_4_ = std::vector<Table*>(four_chair_tables_, new Table(4));
	generator_ = default_random_engine(seed_);

	this->number_of_customers_ = std::vector<int>();
	customers = 0;
	this->system_time_ = std::vector <int> ();
	this->average_queue_tables = std::vector <int> ();
	this->average_queue_buffet = std::vector <int>();
	this->average_queue_cashiers = std::vector <int>();
	this->average_time_for_table = std::vector <int>();
	this->average_time_for_waiter = std::vector <int>();


	this->table_queue_ = std::vector<Group*>();
	this->cashier_queue_ = std::vector<Group*>();
	this->buffet_queue_ = std::vector<Group*>();
	this->serving_queue_= std::vector<Table*>();

	for (auto i = 0; i < waiter_number_; i++)
	{
		waiters_.push_back(new Waiter(this));
	}

	for(auto i=0;i<cash_number_;i++)
	{
		cash_.push_back(new Cash(this));
	}


	for (auto i = 0; i < two_chair_tables_; i++)
	{
		tables_2_.push_back(new Table(2,this));
	}

	for (auto i = 0; i < three_chair_tables_; i++)
	{
		tables_3_.push_back(new Table(3,this));
	}

	for (auto i = 0; i < four_chair_tables_; i++)
	{
		tables_4_.push_back(new Table(4,this));
	}

}

void Restaurant::SetSeed(int s)
{
	generator_ = default_random_engine(rand() % s * (110000) + s * 100000);
}

int Restaurant::GetStartTime()
{
	return start_collecting_data;
}

void Restaurant::SetStartTime(int x)
{
	start_collecting_data = x;
}

int Restaurant::GetNumberOfBuffetSpots() const
{
	return buffet_spot_;
}

void Restaurant::TakeBuffetSpots(int x)
{
	buffet_spot_ = buffet_spot_ - x;
}

void Restaurant::FreeBuffetSpots(int x)
{
	buffet_spot_ = buffet_spot_ + x;
}

Table* Restaurant::table_check() const
{
	if (!this->table_queue_.empty())
	{
		const int num_of_person = this->table_queue_[0]->GetClientsNumber();

		for (auto i : this->tables_2_)
			if (i->GetCurrentClients() == nullptr && (num_of_person == 2 || num_of_person == 1))	return i;

		for (auto i : this->tables_3_)
			if (i->GetCurrentClients() == nullptr && (num_of_person == 3 || num_of_person == 2 || num_of_person == 1))	return i;

		for (auto i : this->tables_4_)
			if (i->GetCurrentClients() == nullptr && (num_of_person == 4 || num_of_person == 3 || num_of_person == 2 || num_of_person == 1))	return i;
	}
	return nullptr;
}

Waiter* Restaurant::waiter_check() const
{
	for (auto i : this->waiters_)
	{
		if (i->GetCurrentTable() == nullptr)	return i;
	}

	return nullptr;
}

Cash* Restaurant::cash_check() const
{
	for (auto i : this->cash_)
	{
		if (i->GetCurrentClients() == nullptr)		return i;
	}

	return  nullptr;
}

int Restaurant::ServiceTime() 
{
	auto x = abs(exponential_dist_food_(generator_)) + abs(exponential_dist_drinks_(generator_));
	return static_cast<int>(x);
}

int Restaurant::ConsumptionTime()
{
	auto x = exponential_dist_eat_(generator_);
	return static_cast<int>(x);
}

int Restaurant::CashierTime()
{
	auto x = exponential_dist_cashier_(generator_);
	return static_cast<int>(x);
}

int Restaurant::BuffetTime()
{
	auto x = normal_dist_buffet_(generator_);
	return static_cast<int>(x);
}

int Restaurant::NewGroupAppear()
{
	auto x = normal_dist_new_group_(generator_);
	return static_cast<int>(x);
}





