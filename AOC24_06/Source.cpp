#include "Elves.h"
#include <set>
using namespace std;
vector < vector<int >> movements = { {0,-1},{1,0} ,{0,1} ,{-1,0} };

vector<int> vecPlus(vector<int>first, vector<int>second)
{
	return { first[0] + second[0],first[1] + second[1] };
}

set<vector<int>> runPath(int x, int y, vector<string>grid, int dir = 0)
{
	set<vector<int>> uniquePositions;
	uniquePositions.insert({ x,y });
	int oldSize = uniquePositions.size();
	while (true)
	{
		vector<int> newPos = vecPlus({ x,y }, movements[dir]);
		bool nextMove = false;
		int newX = newPos[0];
		int newY = newPos[1];
		if (!checkPos(newX, newY, grid))
		{
			break;
		}
		else if (grid[newY][newX] == '#')
		{
			dir++;
			if (dir > 3)
			{
				dir -= 4;
			}
		}
		else
		{
			x = newX;
			y = newY;
			uniquePositions.insert({ x,y });
		}
	}
	return uniquePositions;
}

bool findLoop(int x, int y, vector<string>grid, int dir = 0)
{
	set<vector<int>> uniquePositions;
	uniquePositions.insert({ x,y,dir });
	while (true)
	{
		int oldSize = uniquePositions.size();
		vector<int> newPos = vecPlus({x,y}, movements[dir]);
		bool nextMove = false;
		int newX = newPos[0];
		int newY = newPos[1];
		if (!checkPos(newX, newY, grid))
		{
			return false;
		}
		else if (grid[newY][newX] == '#')
		{
			dir++;
			if (dir > 3)
			{
				dir -= 4;
			}
		}
		else
		{
			x = newX;
			y = newY;
			uniquePositions.insert({ x,y,dir });
			if (uniquePositions.size() == oldSize)
			{
				return true;
			}
		}	
	}
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> grid;
	int total = 0;
	int total2 = 0;
	int startX = -1, startY = -1;
	int dir = 0;

	int counter = 0;
	while (getline(FileName, lineN))
	{
		grid.push_back(lineN);
		int pos = lineN.find("^");
		if (pos != string::npos)
		{
			startX = pos;
			startY = counter;
		}
		counter++;
	}
	counter = 0;
	set<vector<int>> originalPath = runPath(startX, startY, grid);
	total = originalPath.size();
	
	for (auto it = originalPath.begin(); it != originalPath.end();it++)
	{
		vector<int> newPos = *it;
		int x = newPos[0];
		int y = newPos[1];
		print({ x,y });
		vector<string> gridCopy = grid;
		gridCopy[y][x] = '#';
		bool looped = findLoop(startX, startY, gridCopy);
		if (looped)
		{
			total2++;
		}
	}

	cout << endl;
	cout << total << endl;
	cout << total2 << endl;
}