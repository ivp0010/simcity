#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H
#include "cell.h"
#include <iostream>

class industrial : public cell
{
	public:
		
		industrial(cords pos, int index);
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
