#include "Elves.h"
#include <set>
#include <algorithm>
using namespace std;


set<int> checkRules(int toCheck, vector<int>list1, vector<int>list2)
{
	set<int> rules;
	auto point = find(list2.begin(), list2.end(), toCheck);
	while(point !=list2.end())
	{
		int thePoint = point - list2.begin();
		rules.insert(list1[thePoint]);
		point = (find(point+1, list2.end(), toCheck));
		thePoint = point - list2.begin();
	}
	return rules;
}

vector<int> getRelevantRules(int toCheck, vector<int>list1, vector<int>list2)
{
	vector<int> rules;
	auto point = find(list2.begin(), list2.end(), toCheck);
	while (point != list2.end())
	{
		int thePoint = point - list2.begin();
		rules.push_back(list1[thePoint]);
		point = (find(point + 1, list2.end(), toCheck));
		thePoint = point - list2.begin();
	}
	return rules;
}

int getCentre(vector<int> input)
{
	int a = input.size();
	return input[a / 2];
}

bool checkVectorGood(vector<int>toCheck,vector<int>first,vector<int>second)
{
	for (auto it = toCheck.begin(); it != toCheck.end(); it++)
	{
		set<int> after(it + 1, toCheck.end());
		set<int> before = checkRules(*it, first, second);
		set<int> intersection;
		set_intersection(after.begin(), after.end(), before.begin(), before.end(), inserter(intersection, intersection.begin()));
		if (intersection.size() > 0)
		{
			return false;
			break;
		}
	}

}

void swap(vector<int>& theVec, int firstPos, int newPos)
{
	for (int i = firstPos; i < newPos; i++)
	{
		int temp = theVec[i];
		theVec[i] = theVec[i + 1];
		theVec[i + 1] = temp;
	}
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> lines;
	int total = 0;
	int total2 = 0;
	int splitter = -1;
	int i = 0;
	vector<int> first, second;
	vector<vector<int>>toCheck;
	vector<vector<int>>toFix;

	while (getline(FileName, lineN))
	{
		lines.push_back(lineN);
		if (lineN == "")
		{
			splitter = i;
		}
		i++;
	}

	for (int i = 0; i < splitter; i++)
	{
		vector<int> split = splitStringI(lines[i], '|');
		first.push_back(split[0]);
		second.push_back(split[1]);
	}
	for (int i = splitter + 1; i < lines.size(); i++)
	{
		toCheck.push_back(splitStringI(lines[i], ','));
	}
	for (int i = 0; i < toCheck.size(); i++)
	{
		bool good = checkVectorGood(toCheck[i],first,second);
		if (good)
		{
			total += (getCentre(toCheck[i]));
		}
		else
		{
			toFix.push_back(toCheck[i]);
		}
	}
	cout << total << endl;
	for (int i = 0; i < toFix.size(); i++)
	{
		bool good = false;
		vector<int>theVec = toFix[i];	
		int pos = 0;
		while (!good)
		{
			vector<int> after = getRelevantRules(theVec[pos], first, second);
			int newPos = last(theVec, after);
			if (newPos < pos)
			{
				pos++;
			}
			else
			{
				swap(theVec, pos, newPos);
			}
			good = checkVectorGood(theVec, first, second);
		}
		total2 += (getCentre(theVec));
	}
	cout << total2 << endl;
}