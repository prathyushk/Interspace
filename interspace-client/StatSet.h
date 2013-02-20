#ifndef __StatSet_h_
#define __StatSet_h_

#include <string>
#include <vector>
#include "Stat.h"

class StatSet
{
public:
	StatSet(void);
	StatSet(std::string className);
	~StatSet(void);
	float getMaxHealth();
	float getAccuracy();
	float getJump();
	float getSpeed();
	float getDefense();
	float getGunProficiency();
private:
	void loadStats(void);
	void loadJuggernaut(void);
	void loadAcrobat(void);
	void loadSniper(void);
	std::vector<Stat*>* stats;
};

#endif