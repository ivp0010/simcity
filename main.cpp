#include <iostream>
#include <string>
#include "splitter.h"

int main()
{

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










return 0;
}
