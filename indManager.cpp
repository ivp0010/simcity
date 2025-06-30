#include <iostream>
#include <vector>
#include "manager.h"
#include "indManager.h"

void indManager::produceGoods()
{
	for(unsigned int i = 0; i < store.size(); i++)
	{
		for(unsigned int j = 0; j < (unsigned int)store[i]->getSize(); j++)
		{
			store[i]->makeGoods();
		}
	}
}

void indManager::sellGoods(int x)
{
	int count = 0;
	for(unsigned int i = 0; i < store.size(); i++)
	{
		for(unsigned int j = 0; j < (unsigned int)store[i]->getSize(); j++)
		{
			store[i]->useGoods(1);
			count++;
			if(count == x){return;}
		}
		if(count == x){return;}
	}
}

int indManager::getNumGoods()
{
	int count = 0;
	for(unsigned int i = 0; i < store.size(); i++)
	{
		count += store[i]->getGoods();
	}
	return count;
}
