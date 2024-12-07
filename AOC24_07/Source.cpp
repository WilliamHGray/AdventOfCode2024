#include "Elves.h"
using namespace std;

vector<int64_t> doSums(vector<int64_t> input, int second, bool concat=false)
{
	vector<int64_t> output;
	for (int i = 0; i < input.size(); i++)
	{
		output.push_back(input[i] + second);
		output.push_back(input[i] * second);
		if (concat)
		{
			string concatString = to_string(input[i]) + to_string(second);
			output.push_back(stoll(concatString));
		}
	}
	return output;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<int64_t> totals;
	vector<vector<int>> sums;
	int64_t total = 0;
	int64_t total2 = 0;

	while (getline(FileName, lineN))
	{
		vector<string> temp = splitString(lineN, ':');
		totals.push_back(stoll(temp[0]));
		sums.push_back(splitStringI(temp[1], ' '));
	}
	for (int i = 0; i < totals.size(); i++)
	{
		int64_t toFind = totals[i];
		vector<int> values = sums[i];
		vector<int64_t> nextIn = { values[0] };
		vector<int64_t> nextInP2 = { values[0] };
		for (int j = 1; j < values.size(); j++)
		{
			nextIn = doSums(nextIn, values[j]);
			nextInP2 = doSums(nextInP2, values[j], true);
		}
		int results = count(nextIn.begin(), nextIn.end(), toFind);
		int resultsP2 = count(nextInP2.begin(), nextInP2.end(), toFind);
		if (results > 0)
		{
			total += toFind;
		}
		if (resultsP2 > 0)
		{
			total2 += toFind;
		}
	}
	cout << total << endl;
	cout << total2 << endl;
}