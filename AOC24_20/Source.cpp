#include "Elves.h"
#include <set>
#include <map>
#include <algorithm>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

vector<vector<int>> getDistance(vector<string> grid, vector<int> startPos, vector<vector<int>>& orderedPath)
{
	vector<vector<int>> distance;
	distance.resize(grid.size(), vector<int>(grid[0].size(), -1));
	distance[startPos[1]][startPos[0]] = 0;
	set<vector<int>> positions;
	positions.insert(startPos);

	while (!positions.empty())
	{
		auto pos = positions.begin();
		orderedPath.push_back(*pos);
		int oldDistance = distance[(*pos)[1]][(*pos)[0]];
		for (auto move : moves)
		{
			vector<int> newPos = *pos + move;
			if (checkPos(newPos, grid) && grid[newPos[1]][newPos[0]] != '#' && (distance[newPos[1]][newPos[0]] == -1))
			{
				distance[newPos[1]][newPos[0]] = oldDistance + 1;
				positions.insert(newPos);
			}
		}
		positions.erase(pos);
	}

	return distance;
}

int manDiff(vector<int> pos1, vector<int> pos2)
{
	return abs(pos1[0] - pos2[0]) + abs(pos1[1] - pos2[1]);
}

int checkCheat(vector<string> grid, vector<vector<int>> distances, vector<int> wall, bool LR = true)
{
	vector<int> dir1, dir2;
	if (LR)
	{
		dir1 = moves[1];
		dir2 = moves[3];
	}
	else
	{
		dir1 = moves[0];
		dir2 = moves[2];
	}

	vector<int> newPos1 = wall + dir1;
	vector<int> newPos2 = wall + dir2;
	if (checkPos(newPos1, grid) && checkPos(newPos2, grid))
	{
		int d1 = distances[newPos1[1]][newPos1[0]];
		int d2 = distances[newPos2[1]][newPos2[0]];
		int dMax = max(d1, d2);
		int dMin = min(d1, d2);
		if (d1 != -1 && d2 != -1)
		{
			return dMax - dMin - 2;
		}
	}

	return 0;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> grid;
	int total = 0;
	int total2 = 0;
	vector<vector<int>> walls;
	map<int, int> cheats;
	map<int, int> cheatsP2;
	while (getline(FileName, lineN))
	{
		grid.push_back(lineN);
	}
	vector<int> start, end;

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == 'S')
			{
				start = { j,i };
			}
			else if (grid[i][j] == 'E')
			{
				end = { j,i };
			}
			else if (grid[i][j] == '#')
			{
				vector<int> pos = { j,i };
				int nextTo = 0;
				for (auto move : moves)
				{
					vector<int> newPos = pos + move;
					if (checkPos(newPos, grid) && grid[newPos[1]][newPos[0]] != '#')
					{
						nextTo++;
					}
				}
				if (nextTo > 1)
				{
					walls.push_back(pos);
				}
			}
		}
	}
	vector<vector<int>> path;
	vector<vector<int>> distances = getDistance(grid, start, path);

	for (auto wall : walls)
	{
		int timeSaveRL = checkCheat(grid, distances, wall, true);
		int timeSaveUD = checkCheat(grid, distances, wall, false);

		if (timeSaveRL > 0)
		{
			cheats[timeSaveRL]++;
		}
		if (timeSaveUD > 0)
		{
			cheats[timeSaveUD]++;
		}
		if (timeSaveRL > 99 || timeSaveUD > 99)
		{
			total++;
		}
	}

	for (int i = 0; i<path.size()-1; i++)
	{
		for (int j = i + 1; j < path.size(); j++)
		{
			int dist = manDiff(path[i], path[j]);
			int timeDiff = distances[path[j][1]][path[j][0]]-distances[path[i][1]][path[i][0]];
			if (dist <= 20 && timeDiff - dist > 0)
			{
				cheatsP2[timeDiff - dist]++;
				if (timeDiff - dist > 99)
				{
					total2++;
				}
			}
		}
	}
	/* P1 Debug
	* for (auto cheat : cheats) 
	{
		cout << cheat.first << ": " << cheat.second << endl;
	}
	P2 Debug
	for (auto cheat : cheatsP2)
	{
		if(cheat.first>=50)
			cout << cheat.first << ": " << cheat.second << endl;
	}*/
	
	cout << total << endl;
	cout << total2 << endl;
}