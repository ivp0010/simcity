#include <vector>
#include "cell.h"
#include <iostream>
#include "manager.h"

cell* manager::at(int x)
{
	return store[x];
}

void manager::insert(cell* newCell)
{
	store.push_back(newCell);
}

unsigned int manager::size()
{
	return store.size();
}
