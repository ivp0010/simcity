#include "cell.h"
#include "commercial.h"
#include <iostream>

commercial::commercial(cords pos, int index)
{
	this->index = index;
	toInc = false;
	size = 0;
	loc = pos;
	type = 'c';
	priority = 0;
}
