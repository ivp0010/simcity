#include "graph.h"
#include <iostream>
#include <vector>
using namespace std;

                
graph::graph(int size)
{
	adjList.resize(size);
}

void graph::addEdge(int start, int dest)
{
	if(start < 0 || start > (int)adjList.size() - 1){return;}	
	for(auto x : adjList[start]){if(x == dest){return;}}
	adjList[start].push_back(dest);
}

vector<int>* graph::getList(int x)
{
	vector<int>* vec = new vector<int>();
	for(auto t : adjList[x])
	{
		vec->push_back(t);
	}
	return vec;
}

void graph::printAdjList()
{
	for(unsigned int i = 0; i < adjList.size(); i++)
	{
		cout << i << ": ";
		for(auto x : adjList[i])
		{
			cout << x << " ";
		}
		cout << endl;
	}
}
/*
bool graph::validWalk(vector<int> &walk)
{
	bool valid;
	for(unsigned int i = 0; i < walk.size() - 1; i++)
	{
		valid = false;
		for(auto x : adjList[walk[i]])
		{
			if(x == walk[i + 1])
			{
				valid = true;
			}
		}

		if(!valid){return false;}
	}
	return true;
}

void graph::walkAnalysis(vector<int> &walk)
{
	bool closed = false;
	bool trail = false;
	bool path = false;
	bool circuit = false;
	bool cycle = false;

	if(walk[0] == walk[walk.size() - 1])
	{
		closed = true;
	}
	
	bool repeated;

	for(unsigned int i = 0; i < walk.size() - 1; i++)
	{
		repeated = false;

		for(unsigned int j = i + 1; j < walk.size(); j++)
		{
			if(walk[i] == walk[j] && walk[i + 1] == walk[j + 1])
			{
				repeated = true;
				break;
			}
			else if(walk[i] == walk[j + 1] && walk[i + 1] == walk[j])
			{
				repeated = true;
				break;
			}
		}
		if(repeated){break;}
	}

	if(!repeated){trail = true;}
	
	if(trail && closed)
	{
		circuit = true;
	}

	if(trail)
	{
		for(unsigned int i = 0; i < walk.size(); i++)
		{
			repeated = false;
			for(unsigned int j = 0; j < walk.size(); j++)
			{
				if(j == i){continue;}
				if(walk[i] == walk[j])
				{
					repeated = true;
					break;
				}
			}
			if(repeated){break;}
		}
		if(!repeated){path = true;}
	}

	if(circuit)
	{
		for(unsigned int i = 0; i < walk.size() - 1; i++)
		{
			*/
