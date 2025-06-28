#include <iostream>
#include <string>
#include "splitter.h"
#include "simManager.h"

int main()
{
	simManager s;
	std::string filename;
	int rr; //refresh rate;
	int steps;
	std::cout << "filename: ";
	std::cin >> filename;
	std::cout << "refresh rate: ";
	std::cin >> rr;
	std::cout << "number of time steps: ";
	std::cin >> steps;
	std::vector<std::vector<char>> map;
	splitter(map, filename);
	s.init(map, rr, steps);
	s.runSim();	

	







return 0;
}
