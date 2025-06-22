#include "cell.h"
#include "commercial.h"
#include <iostream>

commercial::commercial()
{
	toInc = false;
	size = 0;
	loc = {.x = -1, .y = -1};
}
