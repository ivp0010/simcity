#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>

typedef struct cordinates
{

	int x, y;

}cords;

class cell
{

	public:
		
		cell();
		int getSize();
		void setToInc();
		void resetInc();
	 	cords getLocation(); 

	protected:
		
		int size;
		bool toInc;
		cords loc;
};

#endif
