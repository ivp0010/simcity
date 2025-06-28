#ifndef SPLITTER_H
#define SPLITTER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void splitter(std::vector<std::vector<char>> &map, std::string filename)
{
	std::fstream i_s;
	i_s.open(filename, std::ifstream::in);
	std::string line;

	while(!i_s.eof())
	{
		std::getline(i_s, line);
		std::vector<char> temp;
		for(unsigned int i = 0; i < line.size(); i++)
		{
			if(line.at(i) != ',')
			{
				temp.push_back(line.at(i));
			}
		}
		map.push_back(temp);
	}

	i_s.close();
}

#endif
