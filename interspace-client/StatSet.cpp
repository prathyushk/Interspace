#include "StatSet.h"
#include <string>
#include <vector>
#include "Stats.h"

StatSet::StatSet()
{
	stats = new std::vector<Stat*>();
}

StatSet::StatSet(std::string className)
{
	stats = new std::vector<Stat*>();
	if(className.compare("Juggernaut") == 0)
		loadJuggernaut();
	else if(className.compare("Acrobat") == 0)
		loadAcrobat();
	else if(className.compare("Sniper") == 0)
		loadSniper();
	else
		loadStats();
}

void StatSet::loadStats()
{
	stats->push_back(new Accuracy());
	stats->push_back(new Defense());
	stats->push_back(new GunProficiency());
	stats->push_back(new Jump());
	stats->push_back(new Speed());
	stats->push_back(new Health());
}

void StatSet::loadAcrobat()
{
	stats->push_back(new Accuracy());
	stats->push_back(new Defense());
	stats->push_back(new GunProficiency());
	stats->push_back(new Jump(25));
	stats->push_back(new Speed(1.5));
	stats->push_back(new Health());
}

void StatSet::loadJuggernaut()
{
	stats->push_back(new Accuracy());
	stats->push_back(new Defense(6));
	stats->push_back(new GunProficiency());
	stats->push_back(new Jump());
	stats->push_back(new Speed());
	stats->push_back(new Health(200));
}

void StatSet::loadSniper()
{
	stats->push_back(new Accuracy(55));
	stats->push_back(new Defense());
	stats->push_back(new GunProficiency(5));
	stats->push_back(new Jump());
	stats->push_back(new Speed());
	stats->push_back(new Health());
}