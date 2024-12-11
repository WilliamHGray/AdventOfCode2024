#include "Elves.h"
#include <map>
using namespace std;

// Naive Part 1 Solution
vector<string> iterate(vector<string> stones)
{
	vector<string> newStones;
	for (auto stone : stones)
	{
		if (stone == "0")
		{
			newStones.push_back("1");
		}
		else if (!(stone.size() % 2))
		{
			newStones.push_back(to_string(stoll(stone.substr(0, stone.size() / 2))));
			newStones.push_back(to_string(stoll(stone.substr(stone.size() / 2, -1))));
		}
		else
		{
			newStones.push_back(to_string(stoll(stone) * 2024));
		}
	}
	return newStones;
}

vector<int64_t> iterate(int64_t num)
{
	vector<int64_t> temp;
	string numStr = to_string(num);
	if (num == 0)
	{
		temp.push_back(1);
	}
	else if (!(size(numStr) % 2))
	{
		temp.push_back(stoll(numStr.substr(0, numStr.size() / 2)));
		temp.push_back(stoll(numStr.substr(numStr.size() / 2, -1)));
	}
	else
	{
		temp.push_back(num * 2024);
	}
	return temp;
}

int64_t count(map<int64_t, int64_t> stMap)
{
	int64_t total = 0;
	for (auto it = stMap.begin(); it != stMap.end(); it++)
	{
		total += it->second;
	}
	return total;
}

void print(map<int64_t, int64_t> stMap)
{
	for (auto it : stMap)
	{
		cout << it.first << ": " << it.second << endl;
	}
}

void print(vector<int64_t> vect)
{
	for (auto i : vect)
	{
		cout << i << ", ";
	}
	cout << endl;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> stones;
	int64_t total = 0;
	int64_t total2 = 0;

	getline(FileName, lineN);
	stones = splitString(lineN, { ' ' });
	map<int64_t, int64_t> stonesMap;
	for (auto stone : stones)
	{
		stonesMap[stoll(stone)] = 1;
	}
	vector<int64_t> sizes;
	sizes.push_back(count(stonesMap));

	int numIter = 75;
	for (int i = 0; i < numIter; i++)
	{
		map<int64_t, int64_t> newStonesMap;
		//stones = iterate(stones); Naive part one solution
		for (auto it : stonesMap)
		{
			vector<int64_t> newNums = iterate(it.first);
			for (auto num : newNums)
			{
				newStonesMap[num] += it.second;
			}
		}
		stonesMap = newStonesMap;
		if (i == 24)
		{
			total = count(stonesMap);
			cout << "Part 1: " << total << endl;
		}
		sizes.push_back(count(stonesMap));
	}
	//cout<<stones.size()<<endl;

	cout << "Part 2: " << count(stonesMap) << endl;

	print(sizes);

	//Sizes at each iteration for mathematical analysis
	/* 8, 11, 16, 21, 34, 45, 72, 117, 164, 217, 355, 581, 815, 1229, 1834, 2888, 4384, 6499, 10085, 15014, 22835, 35171, 52948, 80556, 121602, 185205, 283690, 426048, 649687, 989373, 1494837, 2281878, 3454856, 5253971, 7988666, 12086993,
	18444712, 27961628, 42414389, 64588090, 97878875, 148913584, 226091587, 343058773, 522077124, 791622565, 1203222442, 1828701181, 2774120800, 4218579994, 6403575694, 9726702669, 14783033319, 22433563386, 34099956300, 51785448854, 78631553860,
	119507525679, 181423762352, 275643418480, 418712414883, 635778934909, 966111482394, 1467008046049, 2228379282104, 3385387296648, 5140653096488, 7810177165688, 11861889579346, 18016174726252, 27370102963634, 41565026509790, 63141820853270, 95907750360379, 
	145661912159421, 221280540398419*/

}