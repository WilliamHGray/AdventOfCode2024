#include "Elves.h"
using namespace std;

int xSize = 101;
int ySize = 103;
int numIter = 100;
string line = "";

void printTree(vector<vector<int>> positions)
{
	vector<string>grid;
	grid.resize(ySize, line);
	for (auto pos : positions)
	{
		int x = pos[0];
		int y = pos[1];
		grid[y][x] = 'o';
	}
	print(grid);
}

void MOD(vector<int>& first, vector<int> second)
{
	for (int i = 0; i < first.size(); i++)
	{
		while (first[i] < 0)
		{
			first[i] += second[i];
		}
		while (first[i] >= second[i])
		{
			first[i] -= second[i];
		}
	}
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> things;
	vector<vector<int>> positions;
	vector<vector<int>> speed;
	int total = 0;

	for (int i = 0; i < xSize; i++)
	{
		line += '.';
	}

	while (getline(FileName, lineN))
	{
		int first = lineN.find('=')+1;
		int second = lineN.find('=',first)+1;
		positions.push_back(splitStringI(lineN.substr(first, lineN.find(' ') - first), { ',' }));
		speed.push_back(splitStringI(lineN.substr(second), { ',' }));
	}
	
	vector<vector<int>> finalPositions;
	for (int i = 0; i < positions.size(); i++)
	{
		vector<int> newPos = positions[i] + (speed[i] * numIter);
		MOD(newPos, { xSize,ySize });
		finalPositions.push_back(newPos);
		//print(newPos);
	}
	cout << endl;
	vector<vector<int>> quadrants = { {0,0},{0,0} };
	int midX = xSize / 2;
	int midY = ySize / 2;
	for (auto pos : finalPositions)
	{
		if (!(pos[0] == midX || pos[1] == midY))
		{
			int x, y;
			if (midX<pos[0])
			{
				x = 1;
			}
			else
			{
				x = 0;
			}
			if (midY < pos[1])
			{
				y = 1;
			}
			else
			{
				y = 0;
			}
			quadrants[y][x]++;
		}
	}

	print(quadrants);
	cout << quadrants[0][0] * quadrants[0][1] * quadrants[1][0] * quadrants[1][1] << endl;
	
	int it = 0;
	while (true)
	{
		vector<vector<int>> newPositions;
		for (int i = 0; i < positions.size(); i++)
		{
			vector<int> newPos = positions[i] + speed[i];
			MOD(newPos, { xSize,ySize });
			newPositions.push_back(newPos);
		}
		positions = newPositions;
		
		it++;

		if (!((it-7858)%10403)) // General form for iterations with christmas trees; can remove the break to see more
		{
			cout << it << endl;
			printTree(positions);
			cout << endl;
			break;
		}
	}
	



}