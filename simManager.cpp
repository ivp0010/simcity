#include "cell.h"
#include "industrial.h"
#include "residential.h"
#include "commercial.h"
#include <vector>
#include <iostream>
#include "graph.h"
#include "simManager.h"
#include "graph.h"

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
	std::vector<cell*> tempStore;
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
					tempStore.push_back(newCell);
					break;
				}
				case 'i':
				{
					cords temp = {.x = static_cast<int>(j), .y = static_cast<int>(i)};
					cell* newCell = new industrial(temp, k);
					iStore.insert(newCell);
					tempStore.push_back(newCell);
					break;
				}
				case 'c':
				{
					cords temp = {.x = static_cast<int>(j), .y = static_cast<int>(i)};
					cell* newCell = new commercial(temp, k);
					cStore.insert(newCell);
					tempStore.push_back(newCell);
					break;
				}
				default:
				{
					cords temp = {.x = static_cast<int>(j), .y = static_cast<int>(i)};
					cell* newCell = new cell();
					newCell->setLocation(temp);
					newCell->setIndex(k);
					tempStore.push_back(newCell);
					break;
				}
				
			}
			k++;
		}
		k++;
	}

	
	int d[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

	for(unsigned int i = 0; i < size; i++)
	{
	
		for(unsigned int j = 0; j < 8; j++)
		{
			int nx = tempStore[i]->getLocation().x + d[j][0];
			int ny = tempStore[i]->getLocation().y + d[j][1];	
			int idx = getIndex(nx, ny);
			if(idx != -1)
			{

				tracker->addEdge(i, idx);
				tracker->addEdge(idx, i);
			}
		}
		
	}	
}

int simManager::getIndex(int x, int y)
{
	if (y < 0 || y >= startMap.size()){return -1;}
    	if (x < 0 || x >= startMap[y].size()){return -1;}

	int index = 0;
	for(unsigned int i = 0; i < y; i++)
	{
		index += startMap[i].size();
	}
	index += x;
	return index;
}
