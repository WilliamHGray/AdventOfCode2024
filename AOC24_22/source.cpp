#include "elves.h"
#include <map>
#include <set>
using namespace std;
int64_t modNum = 16777216;

void prune(int64_t& num)
{
	while (num > modNum)
	{
		num -= modNum;
	}
}

void run(int64_t& num)
{
	int64_t temp = num * 64;
	temp = temp ^ num;
	prune(temp);
	num = temp;
	temp = num / 32;
	temp = temp ^ num;
	prune(temp);
	num = temp;
	temp = num * 2048;
	temp = temp ^ num;
	prune(temp);
	num = temp;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<int64_t> lines, answers;
	int64_t total = 0;
	int64_t total2 = 0;
	while (getline(FileName, lineN))
	{
		lines.push_back(stoll(lineN));
	}
	int numIter = 2000;
	set<vector<int>> sequences;
	vector<map<vector<int>, int>> monkeyMap;
	map<vector<int>, int> costs;
	for (int64_t num : lines)
	{
		map<vector<int>, int> monkey;
		int d1, d2, d3, d4, oldCost;
		for (int i = 0; i < numIter; i++)
		{
			int oldCost = num % 10;
			run(num);
			int cost = num % 10;
			if (i == 0)
			{
				d3 = cost - oldCost;
			}
			else if (i == 1)
			{
				d2 = cost-oldCost;
			}
			else if (i == 2)
			{
				d1 = cost-oldCost;
			}
			else
			{
				d4 = d3;
				d3 = d2;
				d2 = d1;
				d1 = cost-oldCost;
				vector<int> sequence = { d4,d3,d2,d1 };
				sequences.insert(sequence);
				if (monkey.count(sequence) == 0)
				{
					monkey[sequence] = cost;
					costs[sequence] += cost;
				}
			}
		}
		monkeyMap.push_back(monkey);
		answers.push_back(num);
		total += num;
	}
	for(auto cost:costs)
	{
		int temp = cost.second;
		if (temp > total2)
		{
			total2 = temp;
		}
	}

	std::cout << total << endl;
	std::cout << total2 << endl;
}