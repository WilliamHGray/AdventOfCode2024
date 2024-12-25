#include "elves.h"
using namespace std;

bool compare(vector<int> key, vector<int> lock)
{
	int maxSize = 5;
	for (int i = 0; i < key.size(); i++)
	{
		if (key[i] + lock[i] > maxSize)
		{
			return false;
		}
	}
	return true;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<vector<string>> locks, keys;
	vector<vector<int>> keysI, locksI;
	int64_t total = 0;
	int64_t total2 = 0;
	vector<string> temp;
	while (getline(FileName, lineN))
	{
		if (lineN == "")
		{
			char first = temp[0][0];
			if (first == '#')
			{
				locks.push_back(temp);
			}
			else
			{
				keys.push_back(temp);
			}
			temp.clear();
		}
		else
		{
			temp.push_back(lineN);
		}
	}
	char first = temp[0][0];
	if (first == '#')
	{
		locks.push_back(temp);
	}
	else
	{
		keys.push_back(temp);
	}
	for (auto lock : locks)
	{
		vector<int> temp;
		for (int i = 0; i < lock[0].size();i++)
		{
			int it = -1;
			for (int j = 0; j < lock.size(); j++)
			{
				if (lock[j][i] == '#')
				{
					it++;
				}
				else
				{
					temp.push_back(it);
					break;
				}
			}
		}
		locksI.push_back(temp);
	}

	for (auto key : keys)
	{
		vector<int> temp;
		for (int i = 0; i < key[0].size(); i++)
		{
			int it = -1;
			for (int j = 0; j < key.size(); j++)
			{
				if (key[j][i] == '#')
				{
					it++;
				}
			}
			temp.push_back(it);
		}
		keysI.push_back(temp);
	}
	for (auto key : keysI)
	{
		for (auto lock : locksI)
		{
			if (compare(key, lock))
			{
				total++;
			}
		}
	}
	cout << total << endl;
}