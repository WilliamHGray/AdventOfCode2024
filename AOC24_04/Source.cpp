#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> transpose(vector<string> input) {
	vector<string> newVector;
	newVector.resize(input[0].size());
	for (int i = 0; i < newVector.size(); i++)
	{
		std::string nextWord;
		for (int j = 0; j < input.size(); j++)
		{
			nextWord += input[j][i];
		}
		newVector[i]=(nextWord);
	}
return newVector;
}

vector<string> diagonalise(vector<string>input) {
	vector<string> newVector;
	newVector.resize(2 * input.size() - 1);
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[i].size(); j++)
		{
			newVector[i + j] += input[i][j];
		}
	}
	return newVector;
}


vector<string> reverse(vector<string> input)
{
	vector<string> newVector;
	newVector.resize(input.size());
	for (int i = 0; i < input.size(); i++)
	{
		string temp = input[i];
		newVector[i] = string(temp.rbegin(), temp.rend());
	}
	return newVector;
}


int count(string input, string toFind) {
	int total = 0;
	int pos = input.find(toFind);
	while (pos != string::npos)
	{
		total++;
		pos = input.find(toFind, pos + 1);
	}
	return total;
}

bool checkPos(int i, int j, vector<string> input)
{
	if (i == 0 || j == 0)
	{
		return false;
	}
	int maxsize = input.size();
	if (i == maxsize-1 || j == maxsize-1)
	{
		return false;
	}
	return true;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> wordsearch;
	int total = 0;
	int total2 = 0;

	while (getline(FileName, lineN))
	{
		wordsearch.push_back(lineN);
	}

	vector<string> newVector = transpose(wordsearch);

	vector<string> newVectord = diagonalise(wordsearch);

	vector<string> newVectorRd = diagonalise(reverse(newVector));


	for (int i = 0; i < wordsearch.size(); i++)
	{
		total += count(wordsearch[i], "XMAS");
		total += count(wordsearch[i], "SAMX");
		total += count(newVector[i], "XMAS");
		total += count(newVector[i], "SAMX");
	}

	for (int i = 0; i < newVectorRd.size(); i++)
	{
		total += count(newVectord[i], "XMAS");
		total += count(newVectord[i], "SAMX");
		total += count(newVectorRd[i], "XMAS");
		total += count(newVectorRd[i], "SAMX");
	}

	cout << total << endl;
	for (int i = 0; i < wordsearch.size(); i++)
	{
		for (int j = 0; j < wordsearch.size(); j++)
		{
			if (wordsearch[i][j] == 'A' && checkPos(i, j, wordsearch))
			{
				if ((wordsearch[i - 1][j-1] == 'M' && wordsearch[i + 1][j+1] == 'S') || (wordsearch[i + 1][j+1] == 'M' && wordsearch[i - 1][j-1] == 'S'))
				{
					if ((wordsearch[i+1][j - 1] == 'M' && wordsearch[i-1][j + 1] == 'S') || (wordsearch[i-1][j + 1] == 'M' && wordsearch[i+1][j - 1] == 'S'))
					{
						total2++;
					}
				}
			}
		}
	}
	cout << total2 << endl;
}