#include <iostream>
#include "cell.h"
#include "industrial.h"

industrial::industrial(cords pos, int index)
{
	this->index = index;
	toInc = false;
	pollution = 0;
	size = 0;
	goods = 0;
	loc = pos;
	type = 'i';
	priority = 0;
}


void industrial::incPollution()
{
	pollution++;
}

int industrial::getPollution()
{
	return pollution;
}

void industrial::makeGoods()
{
	goods++;
}

int industrial::getGoods()
{
	return goods;
}

void industrial::useGoods(int x)
{
	goods -= x;

}
