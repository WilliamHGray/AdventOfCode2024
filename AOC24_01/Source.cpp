#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");	
	string lineN;
	vector<int> list1, list2;
	int total = 0;
	while (getline(FileName, lineN))
	{
		int spacepos = lineN.find(" ");
		int num1 = stoi(lineN.substr(0, spacepos));
		int num2 = stoi(lineN.substr(spacepos, -1));
		list1.push_back(num1);
		list2.push_back(num2);
	}
	sort(list1.begin(), list1.end());
	sort(list2.begin(), list2.end());
	for (int i = 0; i < list1.size(); i++)
	{
		total += abs(list1[i] - list2[i]);
	}
	cout << "part 1: " << total << endl;

	total = 0;
	for (int i = 0; i < list1.size(); i++)
	{
		int firstLoc = list1[i];
		int secondPos = 0;
		int numShown = 0;
		while (!(list2[secondPos] > firstLoc))
		{
			if (list2[secondPos] == firstLoc)
			{
				numShown++;
			}
			secondPos++;
		}
		total += (firstLoc * numShown);
	}
	cout << "part 2: " << total << endl;
}