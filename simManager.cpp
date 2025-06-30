#include "cell.h"
#include "industrial.h"
#include "residential.h"
#include "commercial.h"
#include <vector>
#include <iostream>
#include "graph.h"
#include "simManager.h"
#include "graph.h"

void simManager::printMap()
{
	for(unsigned int i = 0; i < changeMap.size(); i++)
	{
		for(unsigned int j = 0; j < changeMap[i].size(); j++)
		{
			std::cout << changeMap[i][j] << " ";
		}
		std::cout << "\n";
	}

	
}

void simManager::updateMap()
{
	while(!rQ.empty())
	{
		int temp = rQ.front();
		rQ.pop();

		switch(gStore[temp]->getType())
		{
			case 'i':
			{
				if(rStore.getNumWorkers() < 2){break;}
				gStore[temp]->grow();
				gStore[temp]->resetInc();
				rStore.getWorkers(2);
				changeMap[gStore[temp]->getLocation().y][gStore[temp]->getLocation().x] = '0' + gStore[temp]->getSize();
				break;
			}
			case 'c':
			{
				if(iStore.getNumGoods() < 1){break;}
				if(gStore[temp]->getSize() > 2){break;}
				if(rStore.getNumWorkers() < 1){break;}
				gStore[temp]->grow();
				gStore[temp]->resetInc();
				rStore.getWorkers(1);
				iStore.sellGoods(1);
				changeMap[gStore[temp]->getLocation().y][gStore[temp]->getLocation().x] = '0' + gStore[temp]->getSize();
				break;
			}
		}
	}




	for(unsigned int i = 0; i < rStore.size(); i++)
	{
		if(rStore.at(i)->getToInc() == true)
		{
			rStore.at(i)->grow();
			rStore.at(i)->resetInc();
			rStore.addWorker(i);
			changeMap[rStore.at(i)->getLocation().y][rStore.at(i)->getLocation().x] = '0' + rStore.at(i)->getSize();
		}
	}
}

void simManager::init(const std::vector<std::vector<char>> &map, int refreshRate, int steps)
{
	startMap = map;
	changeMap = map;
	this->refreshRate = refreshRate;
	this->steps = steps;
	int size = 0;
	for(unsigned int i = 0; i < map.size(); i++)
	{
		size += map[i].size();
	}

	tracker = new graph(size);
	
	unsigned int k = 0;
	
	for(unsigned int i = 0; i < changeMap.size(); i++)
	{
		for(unsigned int j = 0; j < changeMap[i].size(); j++)
		{
			switch(startMap[i][j])
			{
				case 'r':
				{
					cords temp = {.x = static_cast<int>(j), .y = static_cast<int>(i)};
					cell* newCell = new residential(temp, k);
					rStore.insert(newCell);
					gStore.push_back(newCell);
					break;
				}
				case 'i':
				{
					cords temp = {.x = static_cast<int>(j), .y = static_cast<int>(i)};
					cell* newCell = new industrial(temp, k);
					iStore.insert(newCell);
					gStore.push_back(newCell);
					break;
				}
				case 'c':
				{
					cords temp = {.x = static_cast<int>(j), .y = static_cast<int>(i)};
					cell* newCell = new commercial(temp, k);
					cStore.insert(newCell);
					gStore.push_back(newCell);
					break;
				}
				default:
				{
					cords temp = {.x = static_cast<int>(j), .y = static_cast<int>(i)};
					cell* newCell = new cell();
					newCell->setLocation(temp);
					newCell->setIndex(k);
					newCell->setType(changeMap[i][j]);
					gStore.push_back(newCell);
					break;
				}
				
			}
			k++;
		}
	}

	
	int d[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

	for(unsigned int i = 0; i < (unsigned int)size; i++)
	{
	
		for(unsigned int j = 0; j < 8; j++)
		{
			int nx = gStore[i]->getLocation().x + d[j][0];
			int ny = gStore[i]->getLocation().y + d[j][1];	
			int idx = getIndex(nx, ny);
			if(idx != -1)
			{

				tracker->addEdge(i, idx);
				tracker->addEdge(idx, i);
			} 
		}
		
	}
	
	std::cout << "-------------------------------------------------" << std::endl;
	std::cout << "step 0" << std::endl; 
	printMap();
	std::cout << "-------------------------------------------------" << std::endl;
}

int simManager::getIndex(int x, int y)
{
	if (y < 0 || (unsigned int)y > startMap.size()){return -1;}
    	if (x < 0 || (unsigned int)x >= startMap[y].size()){return -1;}

	int index = 0;
	for(unsigned int i = 0; i < (unsigned int)y; i++)
	{
		index += startMap[i].size();
	}
	index += x;
	return index;
}

void simManager::runSim()
{
	for(int i = 0; i < steps; i++)
	{
		resChecker();
		resolver();
		prevMap = changeMap;
		iStore.produceGoods();
		updateMap();
		if(prevMap == changeMap)
		{
			std::cout << "no change has occured during time step " << i << " ending sim.\n";
			std::cout << "final time step:\n";
			printMap();
			runPolSim();
			break;
		}
		if(i % refreshRate == 0)
		{
			std::cout << "-------------------------------------------------" << std::endl;
			std::cout << "step " << i + 1 << std::endl;
			printMap();
			std::cout << "Number of avaliable workers: " << rStore.getNumWorkers() << std::endl;
			std::cout << "Number of goods: " << iStore.getNumGoods() << std::endl;
			std::cout << "-------------------------------------------------" << std::endl;
		}
	}

}

int simManager::adjPopCheck(int index, int min)
{
	std::vector<int>* idxVec = tracker->getList(index);
	int pop = 0;
	for(unsigned int i = 0; i < (unsigned int)idxVec->size(); i++)
	{
		if(gStore[idxVec->at(i)]->getSize() >= min){pop++;}
	}

return pop;
}

int simManager::getAdjPop(int index)
{
	std::vector<int>* idxVec = tracker->getList(index);
	int pop = 0;
	for(unsigned int i = 0; i < (unsigned int)idxVec->size(); i++)
	{
		pop += gStore[idxVec->at(i)]->getSize();
	}

return pop;
}

void simManager::resChecker()
{
	for(unsigned int i = 0; i < (unsigned int)rStore.size(); i++)	
	{
		std::vector<int>* idxVec = tracker->getList(rStore.at(i)->getIndex());
		
		switch(rStore.at(i)->getSize())
		{
			case 0:
			{
				for(unsigned int j = 0; j < (unsigned int)idxVec->size(); j++)
				{
					char temp = gStore[idxVec->at(j)]->getType();
					if(temp == 'T' || temp == '#' || temp == 'P')
					{
						rStore.at(i)->setToInc();
						break;
					}
				}
				if(adjPopCheck(i, 1) > 0)
				{
					rStore.at(i)->setToInc();
					break;
				}
			break;
			}
			case 1:
			{
				if(adjPopCheck(i, 1) > 1)
				{
					rStore.at(i)->setToInc();
					break;
				}
			break;
			}
			case 2:
			{	
				if(adjPopCheck(i, 2) > 3)
				{
					rStore.at(i)->setToInc();
					break;
				}
			break;
			}
			case 3:
			{
				if(adjPopCheck(i, 3) > 5)
				{
					rStore.at(i)->setToInc();
					break;
				}
			break;
			}
			case 4:
			{
				if(adjPopCheck(i, 4) > 7)
				{
					rStore.at(i)->setToInc();
					break;
				}
			break;
			}
		}
	}
}

void simManager::resolver()
{
	
	std::vector<int> idxStore;
	for(unsigned int i = 0; i < (unsigned int)cStore.size(); i++)
	{
		std::vector<int>* idxVec = tracker->getList(cStore.at(i)->getIndex());	
		switch(cStore.at(i)->getSize())
		{
			case 0:
			{
				for(unsigned int j = 0; j < idxVec->size(); j++)
				{
					char temp = gStore[idxVec->at(j)]->getType();
					if(temp == 'T' || temp == '#' || temp == 'P')
					{
						idxStore.push_back(i);
						break;
					}
				}
				if(adjPopCheck(i, 1) > 0)
				{
					idxStore.push_back(i);
					break;
				}
			break;
			}
			case 1:
			{
				if(adjPopCheck(i, 1) > 1)
				{
					cStore.at(i)->priority += 1000;
					idxStore.push_back(i);
					break;
				}
			break;
			}
			default:
			{
				break;
			}
		}
	
	}

	bool swap;
	int points;
	for(unsigned int i = 0; i < (unsigned int)idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < (unsigned int)idxStore.size(); j++)
		{	
			if(getAdjPop(cStore.at(idxStore[i])->getIndex()) < getAdjPop(cStore.at(idxStore[j])->getIndex()))
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}

	points = 10 * idxStore.size();
	for(unsigned int i = 0; i < (unsigned int)idxStore.size(); i++)
	{
		if(i != 0 && getAdjPop(cStore.at(idxStore[i])->getIndex()) == getAdjPop(cStore.at(idxStore[i - 1])->getIndex()))
		{
			cStore.at(idxStore[i])->priority += points;
			continue;
		}

		cStore.at(idxStore[i])->priority += points;
		points = points - (10 * i);
	}

	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < idxStore.size(); j++)
		{	
			if(cStore.at(idxStore[i])->getLocation().y > cStore.at(idxStore[j])->getLocation().y)
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}

	points = 5 * idxStore.size();
	for(unsigned int i = 0; i < (unsigned int)idxStore.size(); i++)
	{
		if(i != 0 && cStore.at(idxStore[i])->getLocation().y == cStore.at(idxStore[i - 1])->getLocation().y)
		{
			cStore.at(idxStore[i])->priority += points;
			continue;
		}

		cStore.at(idxStore[i])->priority += points;
		points = points - (5 * i);
	}

 
	for(unsigned int i = 0; i < (unsigned int)idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < (unsigned int)idxStore.size(); j++)
		{	
			if(cStore.at(idxStore[i])->getLocation().x > cStore.at(idxStore[j])->getLocation().x)
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}

	points = idxStore.size();
	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		if(i != 0 && cStore.at(idxStore[i])->getLocation().x == cStore.at(idxStore[i - 1])->getLocation().x)
		{
			cStore.at(idxStore[i])->priority += points;
			continue;
		}

		cStore.at(idxStore[i])->priority += points;
		points = points - (1 * i);
	}

	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < idxStore.size(); j++)
		{
			if(cStore.at(idxStore[i])->priority < cStore.at(idxStore[j])->priority)
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}

	for(unsigned int i  = 0; i < idxStore.size(); i++)
	{
		rQ.push(cStore.at(idxStore[i])->getIndex());
		cStore.at(idxStore[i])->priority = 0;
	}

	idxStore.clear();
	

	for(unsigned int i = 0; i < iStore.size(); i++)
	{
		std::vector<int>* idxVec = tracker->getList(iStore.at(i)->getIndex());	
		switch(iStore.at(i)->getSize())
		{
			case 0:
			{
				for(unsigned int j = 0; j < idxVec->size(); j++)
				{
					char temp = gStore[idxVec->at(j)]->getType();	
					if(temp == 'T' || temp == '#' || temp == 'P')
					{
						idxStore.push_back(i);
						break;
					}
				}
				if(adjPopCheck(i, 1) > 0)
				{
					idxStore.push_back(i);
					break;
				}
			break;
			}
			case 1:
			{
				if(adjPopCheck(i, 1) > 1)
				{
					iStore.at(i)->priority += 500;
					idxStore.push_back(i);
					break;
				}
			break;
			}
			case 2:
			{
				if(adjPopCheck(i, 2) > 3)
				{
					iStore.at(i)->priority += 1000;
					idxStore.push_back(i);
					break;
				}
			break;
			}

		}
	
	}
	
	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < idxStore.size(); j++)
		{	
			if(getAdjPop(iStore.at(idxStore[i])->getIndex()) < getAdjPop(iStore.at(idxStore[j])->getIndex()))
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}
	
	points = 10 * idxStore.size();
	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		if(i != 0 && getAdjPop(iStore.at(idxStore[i])->getIndex()) == getAdjPop(iStore.at(idxStore[i - 1])->getIndex()))
		{
			iStore.at(idxStore[i])->priority += points;
			continue;
		}

		iStore.at(idxStore[i])->priority += points;
		points = points - (10 * i);
	}

	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < idxStore.size(); j++)
		{	
			if(iStore.at(idxStore[i])->getLocation().y > iStore.at(idxStore[i])->getLocation().y)
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}
	
	points = 5 * idxStore.size();
	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		if(i != 0 && iStore.at(idxStore[i])->getLocation().y == iStore.at(idxStore[i - 1])->getLocation().y)
		{
			iStore.at(idxStore[i])->priority += points;
			continue;
		}

		iStore.at(idxStore[i])->priority += points;
		points = points - (5 * i);
	}
	
	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < idxStore.size(); j++)
		{	
			if(iStore.at(idxStore[i])->getLocation().x > iStore.at(idxStore[i])->getLocation().x)
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}
	
	points = idxStore.size();
	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		if(i != 0 && iStore.at(idxStore[i])->getLocation().x == iStore.at(idxStore[i - 1])->getLocation().x)
		{
			iStore.at(idxStore[i])->priority += points;
			continue;
		}

		iStore.at(idxStore[i])->priority += points;
		points = points - (1 * i);
	}

	for(unsigned int i = 0; i < idxStore.size(); i++)
	{
		swap = false;
		for(unsigned int j = 0; j < idxStore.size(); j++)
		{
			if(iStore.at(idxStore[i])->priority < iStore.at(idxStore[j])->priority)
			{
				int temp = idxStore[i];
				idxStore[i] = idxStore[j];
				idxStore[j] = temp;
				swap = true;
			}
		}
		if(!swap){break;}
	}

	for(unsigned int i  = 0; i < idxStore.size(); i++)
	{
		rQ.push(iStore.at(idxStore[i])->getIndex());
		iStore.at(idxStore[i])->priority = 0;
	}

	idxStore.clear();


}

void simManager::runPolSim()
{
	pollutionMap.resize(startMap.size());
	for(unsigned int i = 0; i < startMap.size(); i++)
	{
		for(unsigned int j = 0; j < startMap[i].size(); j++)
		{
			std::string temp = string(1, startMap[i][j]);
			pollutionMap[i].push_back(temp);
		}
	}
		
	for(unsigned int i = 0; i < iStore.size(); i++)
	{
		if(iStore.at(i)->getSize() == 0){continue;}
		cords temp = iStore.at(i)->getLocation();
		std::string strL = ")";
		std::string strR = "(";
		std::string str = to_string(iStore.at(i)->getSize());
		std::string pollution = strR + str + strL;
		pollutionMap[temp.y][temp.x] += pollution;
	}

	for(int i = 0; i < pollutionMap.size(); i++)
	{
		for(auto x : pollutionMap[i])
		{
			std::cout << x << "    ";
		}
		std::cout << "\n\n";
	}
	
}
