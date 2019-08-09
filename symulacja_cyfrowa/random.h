#pragma once
#include <random>

using namespace std;

class random
{
public:
	random(const int seed);
	~random();

	default_random_engine generator_;
	normal_distribution<double> normal_dist_new_group_ = normal_distribution<double>(1900, 200);
	normal_distribution <double> normal_dist_buffet_ = normal_distribution<double>(3200.0, 100.0); //nie zmieniac 
	exponential_distribution<double> exponential_dist_drinks_ = exponential_distribution<double>(1 / 300.0);
	exponential_distribution<double> exponential_dist_food_ = exponential_distribution<double>(1 / 1700.0);
	exponential_distribution<double> exponential_dist_eat_ = exponential_distribution<double>(1 / 1900.0); //nie zmieniac
	exponential_distribution<double> exponential_dist_cashier_ = exponential_distribution<double>(1 / 200.0);
};

