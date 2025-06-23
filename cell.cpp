#include "cell.h"
#include <iostream>
#include <vector>

cell::cell()
{
	toInc = false;
	size = 0;
	loc = {.x = -1, .y = -1};
}

int cell::getSize()
{
	return size;
}

void cell::setToInc()
{
	toInc = true;
}

void cell::resetInc()
{
	toInc = false;
}

cords cell::getLocation()
{
	return loc;
}

void cell::setLocation(cords newCords)
{
	loc = newCords;
}

void cell::setIndex(int index)
{
	this->index = index;
}

int cell::getIndex()
{
	return index;
}


