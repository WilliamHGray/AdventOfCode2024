#include "Elves.h"
#include <set>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };

vector<vector<int>> makeMove(vector<vector<int>> positions, vector<string> grid, int nextNum)
{
	vector<vector<int>> nextPositions;
	for (auto pos : positions)
	{
		for (auto move : moves)
		{
			vector<int> nextPos = pos + move;
			if (checkPos(nextPos, grid))
			{
				int x = nextPos[0];
				int y = nextPos[1];
				if (grid[y][x] - '0' == nextNum)
				{
					nextPositions.push_back(nextPos);
				}
			}
		}
	}
	return nextPositions;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> grid;
	int total = 0;
	int total1 = 0;
	int total2 = 0;
	vector<vector<int>> startPos;

	while (getline(FileName, lineN))
	{
		grid.push_back(lineN);
	}

	for (int y = 0; y < grid.size(); y++)
	{
		for (int x = 0; x < grid[y].size(); x++)
		{
			if (grid[y][x] == '0')
			{
				startPos.push_back({ x,y });
			}
		}
	}
	
	for (auto pos : startPos)
	{
		vector<vector<int>> nextMoves;
		nextMoves.push_back(pos);
		for (int i = 1; i < 10; i++)
		{
			nextMoves = makeMove(nextMoves, grid, i);
		}
		set<vector<int>>uniqueEnds;
		for (auto ends : nextMoves)
		{
			uniqueEnds.insert(ends);
		}
		total += uniqueEnds.size();
		total2 += nextMoves.size();
	}
	cout << total << endl;
	cout << total2 << endl;
}
