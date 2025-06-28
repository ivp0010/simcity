#ifndef SIMMANAGER_H
#define SIMMANAGER_H
#include "cell.h"
#include "industrial.h"
#include "residential.h"
#include "commercial.h"
#include "resManager.h"
#include "indManager.h"
#include "comManager.h"
#include "manager.h"
#include <vector>
#include <iostream>
#include "graph.h"
#include <queue>

class simManager
{
	public:	
		
		void init(const std::vector<std::vector<char>> &map, int refreshRate, int steps);
		int getIndex(int x, int y);
		void printMap();
		void updateMap();
		void runSim();
		void resChecker();
		int adjPopCheck(int index, int min);
		int getAdjPop(int index);
		void resolver();



	private:

		std::vector<std::vector<char>> startMap;
		std::vector<std::vector<char>> changeMap;
		std::vector<std::vector<char>> prevMap;
		int refreshRate;
		int steps;
		resManager rStore;
		indManager iStore;
		comManager cStore;
		std::vector<cell*> gStore;
		graph* tracker;
		std::queue<int> rQ;

};

#endif
