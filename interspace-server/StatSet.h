#ifndef __StatSet_h__
#define __StatSet_h__

#include <string>
#include <vector>
#include "Stat.h"

class StatSet
{
public:
	StatSet(void);
	StatSet(std::string className);
	~StatSet(void);
private:
	void loadStats(void);
	void loadJuggernaut(void);
	void loadAcrobat(void);
	void loadSniper(void);
	std::vector<Stat*>* stats;
};

#endif