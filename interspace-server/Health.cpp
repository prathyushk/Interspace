#include "Health.h"

Health::Health()
	: Stat("Health", 100, 20)
{
}

Health::Health(float val)
	: Stat("Health", val, 20)
{
}

Health::~Health()
{
}