#include "GunProficiency.h"

GunProficiency::GunProficiency()
	: Stat("GunProficiency", 10, -1)
{
}

GunProficiency::GunProficiency(float val)
	: Stat("GunProficiency", val, -1)
{
}

GunProficiency::~GunProficiency()
{
}