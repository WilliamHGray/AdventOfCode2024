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


	int nextByte = 1800;
	for (int i = 0; i < nextByte; i++)
	{
		vector<int> pos = rems[i];
		grid[pos[1]][pos[0]] = '#';	
	}
	//cout << getDistance(grid, distance) << endl;
	//speed up the process a bit by printing out min dist after n bytes.	


	for (int i = nextByte; i < rems.size(); i++)
	{
		vector<int> pos = rems[i];
		grid[pos[1]][pos[0]] = '#';
		int newDist = getDistance(grid, distance);
		if (newDist == -1)
		{
			print(pos);
			break;
		}
	}
}