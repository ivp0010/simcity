#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H
#include "cell.h"
#include <iostream>
#include <vector>

class residential : public cell
{
	public:
		
		residential();
		bool getEmp(int x);

	private:
		
		std::vector<bool> isEmp;
};

#endif
