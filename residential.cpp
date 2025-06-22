#include <iostream>
#include "cell.h"
#include "residential.h"

residential::residential()
{
	toInc = false;
	size = 0;
	loc = {.x = -1, .y = -1};
}

bool residential::getEmp(int x)
{
	return isEmp[x];
}

