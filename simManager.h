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

class simManager
{
	public:	
		
		void init(const std::vector<std::vector<char>> &map, int refreshRate, int steps);
		int getIndex(int x, int y);

	private:

		std::vector<std::vector<char>> startMap;
		std::vector<std::vector<char>> changeMap;
		int refreshRate;
		int steps;
		resManager rStore;
		indManager iStore;
		comManager cStore;
		graph* tracker;

};

#endif
