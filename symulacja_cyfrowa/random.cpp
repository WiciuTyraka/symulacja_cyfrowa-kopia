#include "random.h"



random::random(const int seed)
{
	generator_ = default_random_engine(seed);
}


random::~random()
{
}
