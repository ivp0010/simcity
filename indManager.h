#ifndef INDMANAGER_H
#define INDMANAGER_H
#include "manager.h"
#include <iostream>
#include <vector>

class indManager : public manager
{
	public:
	
		void produceGoods();
		void sellGoods(int x);
		int getNumGoods();

	private:

};

#endif
