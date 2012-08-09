#ifndef __Health_h_
#define __Health_h_

#include "Stat.h"

class Health : public Stat
{
public:
	Health(void);
	Health(float val);
	~Health(void);
};

#endif