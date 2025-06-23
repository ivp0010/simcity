#include <iostream>
#include <string>
#include "splitter.h"
#include "simManager.h"

int main()
{
	simManager s;
	std::string filename;
	std::cout << "filename: ";
	std::cin >> filename;
	std::vector<std::vector<char>> map;
	splitter(map, filename);

	for(unsigned int i = 0; i < map.size(); i++)
	{
		for(unsigned int j = 0; j < map[i].size(); j++)
		{
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	s.init(map, 1, 10);
	
	







return 0;
}
