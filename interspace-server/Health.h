#ifndef __Health_h__
#define __Health_h__

#include "Stat.h"

class Health : public Stat
{
public:
	Health(void);
	Health(float val);
	~Health(void);
};

#endif