#ifndef __Item_h__
#define __Item_h__

#include <string>
#include "Player.h"

class Item
{
public:
	Item(std::string name,int price,int req,int count,bool stackable,std::string classReq);
	virtual ~Item(void);
	bool isStackable(void);
	std::string getName(void);
	virtual void use(Player* player) = 0;
	int getPrice(void);
	int getCount(void);
	void stack(void);
	void decrement(void);
protected:
	std::string name;
	int price;
	int levelReq;
	int count;
	bool stackable;
	std::string classReq;
};

#endif