#include "Elves.h"
#include <iterator>
using namespace std;

int64_t sumData(vector<int> data)
{
	int64_t total = 0;
	for (int it = 0; it < data.size(); it++)
	{
		if (data[it] != -1)
		{
			total += data[it] * it;
		}
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	int64_t total2 = 0;
	vector<int> data;
	vector<int> data2;
	string datas = "";

	getline(FileName, lineN);
	int it = 0;
	bool write = true;
	for (int i = 0; i < lineN.size(); i++)
	{
		for (int j = 0; j < (lineN[i] - '0'); j++)
		{
			if (write)
			{
				data.push_back(it);
				datas += 'o';
			}
			else
			{
				data.push_back(-1);
				datas += '.';
			}
		}
		if (write)
		{
			it++;
		}
		write = !write;
	}
	data2 = data;
	{	//Part 1
		auto fore = data.begin();
		auto back = data.rbegin();
		while (*fore != -1)
		{
			fore++;
		}
		while (*back == -1)
		{
			back++;
		}
		while (distance(fore, back.base()) > 0)
		{
			int temp = -1;
			*fore = *back;
			*back = temp;
			while (*fore != -1)
			{
				fore++;
			}
			while (*back == -1)
			{
				back++;
			}
		}
		std::cout << sumData(data) << endl;
	}

	{	//Part 2
		auto back = data2.rbegin();
		int numToCopy = 1;
		int strPos = datas.size() - 1;
		while (back != data2.rend())
		{
			if ((back + 1) == data2.rend())
			{
				break;
			}
			if (*back == -1)
			{
				back++;
				strPos--;
			}
			else if (*(back + 1) == *back)
			{
				back++;
				strPos--;
				numToCopy++;
			}
			else
			{
				string numToFind = "";
				for (int i = 0; i < numToCopy; i++)
				{
					numToFind += ('.');
				}
				int found = datas.find(numToFind);
				if (found != string::npos && found<strPos)
				{
					for (int j = 0; j < numToCopy; j++)
					{
						data2[found + j] = *(back - j);
						*(back - j) = -1;
						datas[found + j] = 'o';
						datas[strPos + j] = '.';
					}
				}
				numToCopy = 1;
				back++;
				strPos--;
			}
		}
		std::cout << sumData(data2) << endl;
	}
}