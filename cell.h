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
		void setLocation(cords newCords);
	 	cords getLocation();
		void setIndex(int index);
		int getIndex();

	protected:
		
		int index;
		int size;
		bool toInc;
		cords loc;
};

#endif
