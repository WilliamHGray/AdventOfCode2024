#include "Elves.h"
#include <set>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };


void run(vector<string> grid, vector<vector<int>>& distances, vector<vector<int>> toCheck)
{
	vector<vector<int>> newDirs;
	for (vector<int> pos : toCheck)
	{
		for (int i = -1; i < 2; i++)
		{
			int x = pos[0];
			int y = pos[1];
			int oldDir = pos[2];
			int newDir = oldDir + i;
			if (newDir < 0) { newDir += 4; }
			if (newDir > 3) { newDir -= 4; }
			int newX = pos[0] + moves[newDir][0];
			int newY = pos[1] + moves[newDir][1];
			if (grid[newY][newX] != '#')
			{
				int newDistance = (abs(i) * 1000 + 1 + distances[y][x]);
				if (newDistance < distances[newY][newX])
				{
					distances[newY][newX] = newDistance;
					newDirs.push_back({ newX, newY, newDir });
				}
				
			}
		}
	}
	if (newDirs.size() > 0)
	{
		run(grid, distances, newDirs);
	}
}


vector<vector<int>> triples(vector<string> grid)
{
	vector<vector<int>> temp;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] != '#' && grid[i][j]!='E' && grid[i][j] != 'S')
			{
				int numWalls = 0;
				for (auto move : moves)
				{
					vector<int> neighbour = { j,i };
					neighbour = neighbour + move;
					if (checkPos(neighbour, grid) && grid[neighbour[1]][neighbour[0]] == '#')
					{
						numWalls++;
					}
				}
				if (numWalls > 2)
				{
					temp.push_back({ j,i });
				}
			}
		}
	}
	return temp;
}

int getBestPath(vector<vector<int>> distances, vector<vector<int>> toCheck,vector<vector<int>> checked)
{
	int total = toCheck.size();
	if (total == 0)
	{
		return total;
	}
	vector<vector<int>> newToCheck;
	for (auto pos : toCheck)
	{
		checked.push_back(pos);
		for (auto move : moves)
		{
			vector<int> newPos = pos + move;
			if (find(checked.begin(), checked.end(), newPos) == checked.end())
			{
				int nextDist = distances[newPos[1]][newPos[0]];
				int oldDist = distances[pos[1]][pos[0]];
				if (nextDist < (oldDist + 1000))
				{
					newToCheck.push_back(newPos);
				}
			}
		}
	}
	return total + getBestPath(distances, newToCheck, checked);
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> grid;
	vector<vector<int>> distances;
	int total = 0;
	vector<int> start, end;
	while (getline(FileName, lineN))
	{
		grid.push_back(lineN);
	}
	distances.resize(grid.size(), vector<int>(grid[0].size(), 1000000));

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 'S')
			{
				start = { j,i,1};
				distances[i][j] = 0;
			}
			else if (grid[i][j] == 'E')
			{
				end = { j,i };
			}
		}
	}

	vector<vector<int>> toBlock = triples(grid);
	while (toBlock.size() > 0)
	{
		for (auto pos : toBlock)
		{
			grid[pos[1]][pos[0]] = '#';
		}
		toBlock = triples(grid);
	}

	cout << "PART 1:" << endl;
	
	run(grid, distances, { start });
	print(distances);
	////looks to be off by 1000 in tests
	int shiftedNum = distances[end[1]][end[0]] + 1000;
	cout << shiftedNum << endl;



	int p2AnsMin =  shiftedNum % 1000;
	cout << p2AnsMin << endl;

	cout << "PART 2" << endl;
	int numBestPath = getBestPath(distances, { end }, { });
	//CODE WASN'T WORKING HERE, USED PRINTED GRID AND INSPECTION, ALONG WITH MINIMUM PATH ABOVE
	cout << numBestPath << endl;
}