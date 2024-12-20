#include "Elves.h"
#include <set>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };
int maxSize = 70;
int maxBytes = 1024;

int getDistance(vector<string> grid, vector<vector<int>> distance)
{
	set<vector<int>> positions;
	positions.insert({ 0,0 });

	while (!positions.empty())
	{
		auto pos = positions.begin();
		int oldDistance = distance[(*pos)[1]][(*pos)[0]];
		if ((*pos)[0] == maxSize && (*pos)[1] == maxSize)
		{
			return distance[maxSize][maxSize];
		}
		for (auto move : moves)
		{
			vector<int> newPos = *pos + move;
			if (checkPos(newPos, grid) && grid[newPos[1]][newPos[0]] != '#' && (distance[newPos[1]][newPos[0]] == -1 || distance[newPos[1]][newPos[0]]>oldDistance+1))
			{
				distance[newPos[1]][newPos[0]] = oldDistance + 1;
				positions.insert(newPos);
			}
		}
		positions.erase(pos);
	}

	return -1;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN, line;
	vector<string> grid;
	vector<vector<int>> distance;
	vector<vector<int>> rems;
	for (int i = 0; i <= maxSize; i++)
	{
		line += '.';
	}
	grid.resize(maxSize + 1, line);
	distance.resize(maxSize + 1, vector<int>(maxSize + 1, -1));
	int byte = 0;
	while (getline(FileName, lineN))
	{
		vector<int> pos = splitStringI(lineN, { ',' });	
		byte++;
		if (byte <= maxBytes)
		{
			grid[pos[1]][pos[0]] = '#';
		}
		else
		{
			rems.push_back(pos);
		}
	}
	print(grid);
	distance[0][0] = 0;

	cout << getDistance(grid, distance) << endl;

	int lb = 0;
	int ub = rems.size();
	int mid = (lb + ub) / 2;
	while (lb != mid)
	{
		
		vector<string> grid2 = grid;
		for (int i = lb; i < mid; i++)
		{
			grid2[rems[i][1]][rems[i][0]] = '#';
		}
		int newDist = getDistance(grid2, distance);
		if (newDist == -1)
		{
			ub = mid;
		}
		else
		{
			grid = grid2;
			lb = mid;
		}
		mid = (lb + ub) / 2;
	}
	print(rems[lb]);
}