#ifndef RESMANAGER_H
#define RESMANAGER_H
#include "manager.h"
#include <iostream>
#include <vector>
#include "residential.h"

class resManager : public manager
{
	public:
	
	
		int getNumWorkers();
		bool getWorkers(int x);
		void addWorker(int index);


	private:

};

#endif
