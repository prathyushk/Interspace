#ifndef __Stat_h__
#define __Stat_h__

#include <string>

class Stat
{
public:
	Stat(const std::string name,float start,float inc);
	~Stat(void);
	void increment(void);
	float getVal(void);
	std::string getName(void);
protected:
	float startVal, val, inc;
	std::string name;
};

#endif