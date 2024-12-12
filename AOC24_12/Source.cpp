#include "Elves.h"
#include <set>
#include<algorithm>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };


set<vector<int>> findRegion(vector<int> coord, vector<string> grid)
{
	set<vector<int>> checked;
	set<vector<int>> toCheck;
	char regionType = grid[coord[1]][coord[0]];
	toCheck.insert(coord);
	while (toCheck.size() != 0)
	{
		set<vector<int>> temp;
		for (auto coords : toCheck)
		{
			if (checkPos(coords, grid) && grid[coords[1]][coords[0]] == regionType)
			{
				checked.insert(coords);
				for (auto move : moves)
				{
					vector<int> newPos = coords + move;
					if (checked.find(newPos) == checked.end())
					{
						temp.insert(coords + move);
					}

				}
			}
		}
		toCheck = temp;
	}
	return checked;
}


int countCorners(set<vector<int>> region)
{
	int corners = 0;
	int internalCorners = 0;
	int singleCorners = 0;
	for (auto coord : region)
	{
		for (int i = 0; i < 4; i++)
		{
			int j = i + 1;
			if (j > 3)
			{
				j -= 4;
			}
			vector<int> first = coord + moves[i];
			vector<int> second = coord + moves[j];
			vector<int> third = coord + moves[i] + moves[j];
			bool foundFirst = (region.find(first) != region.end());
			bool foundSecond = (region.find(second) != region.end());
			bool foundThird = (region.find(third) != region.end());
			int numNeighbours = (foundFirst + foundSecond + foundThird);
			if (numNeighbours == 2 && !foundThird)
			{
				corners++;
			}
			else if (numNeighbours == 0)
			{
				corners++;
			}
			else if (numNeighbours == 1 && foundThird)
			{
				corners++;
			}
		}
	}
	return corners;
}

void print(set<vector<int>> coords)
{
	for (auto coord : coords)
	{
		print(coord);
	}
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> grid;
	set<vector<int>> checked;
	int total = 0;
	int total2 = 0;

	while (getline(FileName, lineN))
	{
		grid.push_back(lineN);
	}

	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			if (checked.find({ x,y }) == (checked.end()))
			{
				set<vector<int>> region = findRegion({ x,y }, grid);
				int area = region.size();
				int perimeter = 0;
				int sides = countCorners(region);
				for (auto coord : region)
				{
					for (auto move : moves)
					{
						vector<int> newCoord = coord + move;
						if (region.find(newCoord) == region.end())
						{
							perimeter++;
						}
					}
				}
				checked.insert(region.begin(), region.end());
				total += (area * perimeter);
				total2 += (area * sides);
			}
			
		}
	}
	cout << total << endl;
	cout << total2 << endl;
}