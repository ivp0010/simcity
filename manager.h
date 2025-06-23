#ifndef MANAGER_H
#define MANAGER_H
#include "cell.h"
#include <vector>
#include <iostream>

class manager
{

	public:

		cell* at(int x);
		void insert(cell* newCell);

	protected:

		std::vector<cell*> store;

};

#endif
