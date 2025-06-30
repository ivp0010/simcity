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
		void setType(char type);
		char getType();
		void grow();
		bool getToInc();
		int priority;
		std::vector<bool>&  getEmp();
		void addWorker();
		virtual void incPollution();
		virtual int getPollution();
		virtual void makeGoods();
		virtual int getGoods();
		virtual void useGoods(int x);


	protected:
		
		int index;
		int size;
		bool toInc;
		cords loc;
		char type;
		std::vector<bool> isEmp;
};

#endif
