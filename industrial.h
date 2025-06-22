#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H
#include "cell.h"
#include <iostream>

class inudstrial : public cell
{
	public:
		
		industrial();
		void incPollution();
		int getPollution();
		void makeGoods();
		int getGoods();
		void useGoods(int x);
	
	private:

		int pollution;
		int goods;

};

#endif
