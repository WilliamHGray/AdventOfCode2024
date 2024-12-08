#include "Elves.h"
#include <set>
using namespace std;

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> grid;
	vector<vector<int>> nodes;
	set<vector<int>> antinodes;
	set<vector<int>> antinodesP2;
	int total = 0;

	while (getline(FileName, lineN))
	{
		grid.push_back(lineN);
	}

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size();j++)
		{
			if (grid[i][j] != '.')
			{
				nodes.push_back({ grid[i][j],j,i });
			}
		}
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes.size(); j++)
		{
			if (j != i && nodes[i][0]==nodes[j][0])
			{
				int x1 = nodes[i][1];
				int y1 = nodes[i][2];
				int x2 = nodes[j][1];
				int y2 = nodes[j][2];
				vector<int> first = { x1,y1 };
				vector<int> second = { x2,y2 };
				vector<int> newPos = (second*2) - first;
				antinodesP2.insert(first);
				if (checkPos(newPos, grid))
				{
					antinodes.insert(newPos);
				}
				while (checkPos(newPos, grid))
				{
					antinodesP2.insert(newPos);
					vector<int>tempNewPos = (newPos * 2) - second;
					second = newPos;
					newPos = tempNewPos;
				}
				
			}
		}
	}

	cout << antinodes.size() << endl;
	cout << antinodesP2.size() << endl;
}