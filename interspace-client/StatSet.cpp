#include "StatSet.h"
#include <string>
#include <vector>
#include "Stats.h"
#include "Classes.h"

StatSet::StatSet()
{
	stats = new std::vector<Stat*>();
	loadStats();
}

StatSet::StatSet(std::string className)
{
	stats = new std::vector<Stat*>();
	if(className.compare(Classes::JUGGERNAUT) == 0)
		loadJuggernaut();
	else if(className.compare(Classes::ACROBAT) == 0)
		loadAcrobat();
	else if(className.compare(Classes::SNIPER) == 0)
		loadSniper();
	else
		loadStats();
}

StatSet::~StatSet()
{
	delete stats;
}

float StatSet::getMaxHealth()
{
	return stats->at(5)->getVal();
}

float StatSet::getAccuracy()
{
	return stats->at(0)->getVal();
}

float StatSet::getDefense()
{
	return stats->at(1)->getVal();
}

float StatSet::getGunProficiency()
{
	return stats->at(2)->getVal();
}

float StatSet::getJump()
{
	return stats->at(3)->getVal();
}

float StatSet::getSpeed()
{
	return stats->at(4)->getVal();
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