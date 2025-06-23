#include <iostream>
#include "cell.h"
#include "residential.h"

residential::residential(cords pos, int index)
{
	this->index = index;
	toInc = false;
	size = 0;
	loc = pos;
}

bool residential::getEmp(int x)
{
	return isEmp[x];
}

