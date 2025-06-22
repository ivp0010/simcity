#include <iostream>
#include "cell.h"
#include "industrial.h"

industrial::industrial()
{
	toInc = false;
	pollution = 0;
	size = 0;
	goods = 0;
}


void incPollution()
{
	pollution++;
}

int getPollution()
{
	return pollution;
}

void makeGoods()
{
	goods++;
}

int getGoods()
{
	return goods;
}

void useGoods(int x)
{
	goods - x
}
