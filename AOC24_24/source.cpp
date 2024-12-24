#include "elves.h"
#include <map>
#include <queue>
#include <set>
using namespace std;

int64_t printBinary(map<string, int> reg, set<string> letters)
{
	int64_t total = 0;
	int it = 0;
	for (string s : letters)
	{
		int64_t bit = ((int64_t)reg[s] << it++);
		total += bit;
	}
	cout << total << endl;
	return total;
}


int main() {
	ifstream FileName;
	FileName.open("test3.txt");
	string lineN;
	map<string, int> reg;
	set<string> xes, ys, zeds;
	queue<vector<string>> lines;
	int64_t total = 0;
	int64_t total2 = 0;
	bool first = true;
	while (getline(FileName, lineN))
	{
		if (lineN == "" && first)
		{
			first = false;
		}
		else if (first)
		{
			vector<string> l = splitString(lineN, ':');
			reg[l[0]] = stoi(l[1]);
			if (l[0][0] == 'x')
			{
				xes.insert(l[0]);
			}
			else if (l[0][0] == 'y')
			{
				ys.insert(l[0]);
			}
		}
		else
		{
			vector<string> l = splitString(lineN, ' ');
			vector<string> s = { l[4], l[1], l[0], l[2] };
			lines.push(s);
		}
	}

	int oldSize = 0;
	int newSize = lines.size();
	while (oldSize != newSize)
	{
		oldSize = lines.size();
		queue<vector<string>> temp;
		while (!lines.empty())
		{
			vector<string> l = lines.front();
			lines.pop();
			if (!(reg.count(l[2])) || !(reg.count(l[3])))
			{
				temp.push(l);
			}
			else
			{
				string first = l[2];
				string second = l[3];
				string op = l[1];
				if (l[0][0] == 'z')
				{
					zeds.insert(l[0]);
				}

				if (op == "AND")
				{
					reg[l[0]] = reg[first] & reg[second];
				}
				else if (op == "OR")
				{
					reg[l[0]] = reg[first] | reg[second];
				}
				else if (op == "XOR")
				{
					reg[l[0]] = reg[first] ^ reg[second];
				}
			}
		}
		newSize = temp.size();
		lines = temp;
	}

	int64_t x = printBinary(reg, xes);
	int64_t y = printBinary(reg, ys);
	cout << x + y << endl;

	cout << endl;
	total = printBinary(reg, zeds);
	cout << total - (x + y) << endl;
	//cout << total << endl;
	
	for (string s : xes)
	{
		cout << reg[s];
	}
	cout << endl;
	for (string s : ys)
	{
		cout << reg[s];
	}
	cout << endl;
	for (string s : zeds)
	{
		cout << reg[s];
	}
	cout << endl;

	//Solve part 2 manually by using the rules; XOR must either input X and Y, or ouput Z. Not both.
	//X_k XOR Y_k -> n implies n XOR something else -> X_k
}