#include "Stat.h"
#include <string>

Stat::Stat(const std::string inputName, float start, float inputInc)
{
	name = inputName;
	startVal = start;
	val = start;
	inc = inputInc;
}

Stat::~Stat()
{
}

void Stat::increment()
{
	val += inc;
}

float Stat::getVal()
{
	return val;
}

std::string Stat::getName()
{
	return name;
}