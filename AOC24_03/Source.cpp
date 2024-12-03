#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	int total = 0;
	int total2 = 0;
	bool doing = true;
	while (getline(FileName, lineN))
	{
		int nextStart = lineN.find("mul");
		while (nextStart != string::npos)
		{
			int doIt = lineN.rfind("do()", nextStart);
			int dont = lineN.rfind("don't()", nextStart);
			if (doIt != string::npos && doIt > dont)
			{
				doing = true;
			}
			else if (dont != string::npos && dont > doIt)
			{
				doing = false;
			}
			//lineN = lineN.substr(nextStart, -1);			
			int open = lineN.find("(", nextStart);
			int close = lineN.find(")", nextStart);
			if (open == nextStart+3 && close != string::npos)
			{
				std::cout << lineN.substr(nextStart+3,close-open+1) << endl;
				bool good = true;
				int comma=-1;
				for (int i = open+1; i < close; i++)
				{
					char point = lineN[i];
					if (point == ',')
					{
						if (comma != -1)
						{
							good = false;
							break;
						}
						comma = i;
					}
					else if (point < 48 || point > 57)
					{
						good = false;
						break;
					}
				}
				if (good && comma != -1)
				{
					comma -= nextStart;
					int num1 = stoi(lineN.substr(nextStart+4, comma-1));
					int num2 = stoi(lineN.substr(nextStart+comma+1, close-1));
					//cout << num1 << ", " << num2 << endl;
					total += (num1 * num2);
					if (doing)
					{
						total2 += (num1 * num2);
					}
				}
			}
			nextStart = lineN.find("mul", nextStart+3);
		}
	}
	std::cout << total << endl;
	std::cout << total2 << endl;
}