#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> splitString(string input)
{
	vector<int> line;
	int pos = input.find(" ");
	while (pos != string::npos)
	{
		line.push_back(stoi(input.substr(0, pos)));
		input = input.substr(pos + 1, -1);
		pos = input.find(" ");
	}
	line.push_back(stoi(input.substr(0, -1)));
	return line;
}

bool checkDiff(int num1, int num2, int sign)
{
	int maxDiff = 3 *sign;
	int minDiff = 1 * sign;
	if (sign < 0)
	{
		maxDiff = 1 * sign;
		minDiff = 3 * sign;
	}
	int diff = num2 - num1;
	if (diff <= maxDiff && diff >= minDiff)
	{
		return true;
	}
	return false;
}

int countNumProblems(vector<int> report, bool dampen = false)
{

	int sign;
	int numProbs = 0;
	
	if (dampen)
	{
		int minProbs = 100;
		for (int i = 0; i < report.size();i++)
		{
			int probs = 0;
			vector<int> tempVector = report;
			tempVector.erase(tempVector.begin()+i);
			if (tempVector[0] > tempVector[1])
			{
				sign = -1;
			}
			else
			{
				sign = 1;
			}
			for (int j = 0; j < tempVector.size() - 1; j++)
			{
				bool result = checkDiff(tempVector[j], tempVector[j + 1], sign);
				if (!result)
				{
					probs++;
				}
			}
			if (probs < minProbs)
			{
				minProbs = probs;
			}
		}
		numProbs = minProbs;
	}
	else
	{
		if (report[0] > report[1])
		{
			sign = -1;
		}
		else
		{
			sign = 1;
		}
		for (int j = 0; j < report.size() - 1; j++)
		{
			bool result = checkDiff(report[j], report[j + 1], sign);
			if (!result)
			{
				numProbs++;
			}
		}
	}
	return numProbs;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<vector<int>> reports;
	int total = 0;
	int total2 = 0;

	while (getline(FileName, lineN))
	{
		reports.push_back(splitString(lineN));
	}

	for (int i = 0; i < reports.size(); i++)
	{
		int numProbs = countNumProblems(reports[i]);
		if (numProbs == 0)
		{
			total++;
		}
		numProbs = countNumProblems(reports[i], true);
		if (numProbs == 0)
		{
			total2++;
		}
	}
	cout << total << endl;
	cout << total2 << endl;
}