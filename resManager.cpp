#include "resManager.h"
#include "manager.h"
#include <iostream>
#include <vector>
				
int resManager::getNumWorkers()
{
	int count = 0;
	for(unsigned int i = 0; i < static_cast<unsigned int>(store.size()); i++)
	{
		for(unsigned int j = 0; j < static_cast<unsigned int>(store[i]->getSize()); j++)
		{
			if(store[i]->getEmp()[j] == false){count++;}
		}
	}
	return count;
}

bool resManager::getWorkers(int x)
{
	if(getNumWorkers() < x){return false;}
unsigned int i = 0;
	while(x != 0)
	{
		for(unsigned int j = 0; j < static_cast<unsigned int>(store[i]->getSize()); j++)
		{
			if(store[i]->getEmp()[j] == false)
			{
				x--;
				store[i]->getEmp()[j] = true;
				break;
			}
		}
		i++;
	}
	return true;
}



void resManager::addWorker(int index)
{
	store[index]->addWorker();
}






