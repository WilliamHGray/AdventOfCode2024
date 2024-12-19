#include "Elves.h"
#include <map>
#include <algorithm>
using namespace std;

vector<vector<int>> moves = { {0,-1},{1,0},{0,1},{-1,0} };
int maxSize = 1;


int64_t getNumTowels(string towels, map<string, int64_t>& numTowels, vector<string> patterns)
{
	if (numTowels.count(towels)==1)
	{
		return numTowels[towels];
	}
	else if (towels.size() == 1 && find(patterns.begin(), patterns.end(), towels) != patterns.end())
	{
		numTowels[towels] = 1;
		return numTowels[towels];
	}
	else if (towels.size()>1)
	{
		int tempMaxSize = min(maxSize, (int)towels.size()-1);
		int64_t possibleWays = 0;
		for (int i = 1; i <= tempMaxSize; i++)
		{
			string t1 = towels.substr(0, i);
			if (find(patterns.begin(), patterns.end(), t1) != patterns.end())
			{
				int64_t size2 = getNumTowels(towels.substr(i), numTowels,patterns);
				possibleWays += size2;
			}
		}
		if (patterns.size() > 0 && find(patterns.begin(), patterns.end(), towels) != patterns.end())
		{
			possibleWays++;
		}
		numTowels[towels] = possibleWays;
		
		return numTowels[towels];
	}
	return 0;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> patterns, towels;
	int total = 0;
	int64_t total2 = 0;
	bool first = true;
	map<string, int64_t> numTowels;
	while (getline(FileName, lineN))
	{
		if (lineN == "")
		{
			first = false;
		}
		else if (first)
		{
			patterns = splitString(lineN, { ',' });
		}
		else
		{
			towels.push_back(lineN);
		}
	}

	for (string pattern : patterns)
	{
		if (pattern.size() > maxSize)
		{
			maxSize = pattern.size();
		}
	}

	for (int i = 1; i <= maxSize; i++)
	{
		for (string pattern : patterns)
		{
			if (pattern.size() == i)
			{
				getNumTowels(pattern, numTowels, patterns);
			}
		}
	}

	int it = 0;
	for (string towel : towels)
	{
		cout << ++it << " of " << towels.size() << endl;
		int64_t numWays = getNumTowels(towel, numTowels, patterns);
		cout << towel << ", " << numWays << endl;
		total2 += numWays;
		if (numWays > 0)
		{
			total++;
		}
	}
	cout << total << endl;
	cout << total2 << endl;
}