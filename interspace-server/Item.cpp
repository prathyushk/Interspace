#include "Item.h"
#include <string>

Item::Item(std::string inputName,int inputPrice, int inputReq, int inputCount, bool inputStackable, std::string inputClassReq)
	:name(inputName),price(inputPrice),levelReq(inputReq),count(inputCount),stackable(inputStackable),classReq(inputClassReq)
{
}

Item::~Item()
{
}

bool Item::isStackable()
{
	return stackable;
}

std::string Item::getName()
{
	return name;
}

int Item::getPrice()
{
	return price;
}

int Item::getCount()
{
	return count;
}

void Item::stack()
{
	count++;
}

void Item::decrement()
{
	count--;
}