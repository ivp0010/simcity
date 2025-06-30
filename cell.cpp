#include "cell.h"
#include <iostream>
#include <vector>

cell::cell()
{
	toInc = false;
	size = 0;
	loc = {.x = -1, .y = -1};
	type = ' ';
}

void cell::setType(char type)
{
	this->type = type;
}

int cell::getSize()
{
	return size;
}

void cell::grow()
{
	size++;
}

void cell::setToInc()
{
	toInc = true;
}

void cell::resetInc()
{
	toInc = false;
}

bool cell::getToInc()
{
	return toInc;
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

char cell::getType()
{
	return type;
}

std::vector<bool>& cell::getEmp()
{
	return isEmp;
}

void cell::addWorker()
{
	isEmp.push_back(false);
}

void cell::incPollution(){}

int cell::getPollution(){return NULL;}

void cell::makeGoods(){}

int cell::getGoods(){return NULL;}

void cell::useGoods(int x){}

