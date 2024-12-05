#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#pragma once

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

vector<string> splitString(string input, char toSplit)
{
	vector<string> line;
	int pos = input.find(toSplit);
	while (pos != string::npos)
	{
		line.push_back(input.substr(0, pos));
		input = input.substr(pos + 1, -1);
		pos = input.find(toSplit);
	}
	line.push_back(input.substr(0, -1));
	return line;
}

vector<int> splitStringI(string input, char toSplit)
{
	vector<int> line;
	int pos = input.find(toSplit);
	while (pos != string::npos)
	{
		line.push_back(stoi(input.substr(0, pos)));
		input = input.substr(pos + 1, -1);
		pos = input.find(toSplit);
	}
	line.push_back(stoi(input.substr(0, -1)));
	return line;
}

int firstPos(string input, vector<char> list)
{
	int min = INT_MAX;
	for (int i = 0; i < list.size(); i++)
	{
		int next = input.find(list[i]);
		if (next != string::npos && next < min)
		{
			min = next;
		}
	}
	if (min == INT_MAX)
	{
		min = -1;
	}
	return min;
}

int last(vector<int> input, vector<int> list)
{
	int max = -1;
	for (int i = 0; i < list.size(); i++)
	{
		auto point = find(input.begin(), input.end(), list[i]);
		int next = point - input.begin();
		if (point != input.end() && next > max)
		{
			max = next;
		}
	}
	return max;
}

void print(vector<string> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		cout << "**" << input[i] << "**" << endl;
	}
	cout << endl;
}

void print(vector<int>input)
{
	for (int i = 0; i < input.size(); i++)
	{
		cout << input[i] << " ";
	}
	cout << endl;
}

vector<string> splitString(string input, vector<char> toSplit)
{
	vector<string> line;
	int pos = firstPos(input, toSplit);
	while (pos != string::npos)
	{
		string sub = input.substr(0, pos);
		if (sub != "")
			line.push_back(sub);
		input = input.substr(pos + 1, -1);
		pos = firstPos(input, toSplit);
	}
	line.push_back(input.substr(0, -1));
	return line;
}