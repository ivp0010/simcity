#include "cell.h"
#include <iostream>
#include <vector>

cell::cell()
{
	toInc = false;
	size = 0;
	loc = {.x = 0, .y = 0};
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
