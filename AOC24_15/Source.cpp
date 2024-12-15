#include "Elves.h"
#include <set>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };
vector<char> arrows = { '^','>','v','<' };

bool checkEmpty(vector<int> positions, int yPos, int yDir, vector<string>& grid)
{
	vector<int> nextToCheck;
	for (auto pos : positions)
	{
		char elem = grid[yPos][pos];
		if (elem == '#')
		{
			return false;
		}
		else if (grid[yPos][pos] == ']')
		{
			nextToCheck.push_back(pos);
			nextToCheck.push_back(pos - 1);
		}
		else if (grid[yPos][pos] == '[')
		{
			nextToCheck.push_back(pos);
			nextToCheck.push_back(pos + 1);
		}
	}

	set<int> tempSet;
	tempSet.insert(nextToCheck.begin(), nextToCheck.end());
	while (!nextToCheck.empty())
	{
		nextToCheck.pop_back();
	}
	for (int i : tempSet)
	{
		nextToCheck.push_back(i);
	}

	if (nextToCheck.size() == 0)
	{
		return true;
	}
	else if (checkEmpty(nextToCheck, yPos + yDir, yDir, grid))
	{
		for (int i : nextToCheck)
		{
			grid[yPos + yDir][i] = grid[yPos][i];
			grid[yPos][i] = '.';
		}
		return true;
	}
	return false;
}

void makeMove(vector<int>& roboPos, vector<int> newPos, vector<string>& grid, bool p2 = false)
{
	vector<int> newRoboPos = roboPos + newPos;
	vector<int> currSpace = newRoboPos;
	char currPos = getEl(grid, currSpace);
	if (currPos == '.')
	{
		grid[roboPos[1]][roboPos[0]] = '.';
		roboPos = newRoboPos;
		grid[roboPos[1]][roboPos[0]] = '@';
		return;
	}
	if (p2 && newPos == moves[0] || newPos == moves[2])
	{
		vector<int> toCheck;
		toCheck.push_back(newRoboPos[0]);
		bool canMove = checkEmpty(toCheck, newRoboPos[1], newPos[1], grid);
		if (canMove)
		{
			grid[roboPos[1]][roboPos[0]] = '.';
			grid[newRoboPos[1]][newRoboPos[0]] = '@';
			roboPos = newRoboPos;
		}
	}
	else
	{
		while (currPos != '#')
		{
			currSpace = currSpace + newPos;
			currPos = getEl(grid, currSpace);
			if (currPos == '.' && !p2)
			{
				grid[currSpace[1]][currSpace[0]] = 'O';
				grid[newRoboPos[1]][newRoboPos[0]] = '@';
				grid[roboPos[1]][roboPos[0]] = '.';
				roboPos = newRoboPos;

				break;
			}
			if (currPos == '.' && p2)
			{
				for (auto it = currSpace; it != newRoboPos; it = it - newPos)
				{
					int currX = it[0];
					int currY = it[1];
					int prevX = (it - newPos)[0];
					int prevY = (it - newPos)[1];
					grid[currY][currX] = grid[prevY][prevX];
				}
				grid[roboPos[1]][roboPos[0]] = '.';
				grid[newRoboPos[1]][newRoboPos[0]] = '@';
				roboPos = newRoboPos;
				break;
			}
		}
	}
	return;
}

int score(vector<string> grid, char toFind)
{
	int total = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == toFind)
			{
				total += (100 * i + j);
			}
		}
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> grid;
	vector<string> grid2;
	vector<string> dirs;
	int total = 0;
	int total2 = 0;
	vector<int> roboPos;
	vector<int> roboPos2;
	bool map = true;
	while (getline(FileName, lineN))
	{
		if (lineN == "")
		{
			map = false;
		}
		else if (map)
		{
			grid.push_back(lineN);
		}
		else
		{
			dirs.push_back(lineN);
		}
	}
	grid2.resize(grid.size());

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == '@')
			{
				roboPos = { j,i };
				roboPos2 = { 2 * j,i };
				grid2[i] += "@.";
			}
			else if (grid[i][j] == '.')
			{
				grid2[i] += "..";
			}
			else if (grid[i][j] == 'O')
			{
				grid2[i] += "[]";
			}
			else if (grid[i][j] == '#')
			{
				grid2[i] += "##";
			}
		}
	}
	//print(grid2);

	for (string line : dirs)
	{
		for (char dir : line)
		{
			int index = find(arrows.begin(), arrows.end(), dir) - arrows.begin();
			vector<int> newPos = moves[index];
			makeMove(roboPos, newPos, grid);
			makeMove(roboPos2, newPos, grid2, true);
			//print(grid2);
		}
	}
	print(grid2);

	total = score(grid, 'O');
	total2 = score(grid2, '[');


	cout << total << endl;
	cout << total2 << endl;
}