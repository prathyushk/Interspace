#include "Accuracy.h"

Accuracy::Accuracy()
	: Stat("Accuracy", 50, 2)
{
}

Accuracy::Accuracy(float val)
	: Stat("Accuracy", val, 2)
{
}

Accuracy::~Accuracy()
{
}