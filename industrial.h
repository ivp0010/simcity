#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H
#include "cell.h"
#include <iostream>

class industrial : public cell
{
	public:
		
		industrial(cords pos, int index);
		void incPollution() override;
		int getPollution() override;
		void makeGoods() override;
		int getGoods() override;
		void useGoods(int x) override;

	private:

		int pollution;
		int goods;
};

#endif
