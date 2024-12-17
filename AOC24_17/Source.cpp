#include "Elves.h"
using namespace std;

int64_t combo(int input, int64_t A, int64_t B, int64_t C)
{
	if (input < 4)
	{
		return input;
	}
	else if (input == 4)
	{
		return A;
	}
	else if (input == 5)
	{
		return B;
	}
	else if (input == 6)
	{
		return C;
	}
}

vector<int> run(vector<int> instructions, int64_t A, int64_t B, int64_t C, bool out = false)
{
	vector<int> output;
	int pos = 0;
	while (pos < instructions.size())
	{
		int posJump = 2;
		if (pos + 1 == instructions.size())
		{
			break;
		}
		else if (instructions[pos] == 0)
		{
			int64_t denom = pow(2, combo(instructions[pos + 1], A, B, C));
			A = A / denom;
		}
		else if (instructions[pos] == 1)
		{
			B = B ^ instructions[pos + 1];
		}
		else if (instructions[pos] == 2)
		{
			int64_t val = combo(instructions[pos + 1], A, B, C);
			while (val > 7)
			{
				val -= 8;
			}
			B = val;
		}
		else if (instructions[pos] == 3)
		{
			if (A != 0)
			{
				pos = instructions[pos + 1];
				posJump = 0;
			}
		}
		else if (instructions[pos] == 4)
		{
			B = B ^ C;
		}
		else if (instructions[pos] == 5)
		{
			int64_t val = combo(instructions[pos + 1], A, B, C);
			while (val > 7)
			{
				val -= 8;
			}
			if (out)
			{
				cout << val << ",";
			}
			output.push_back(val);
		}
		else if (instructions[pos] == 6)
		{
			int64_t denom = pow(2, combo(instructions[pos + 1], A, B, C));
			B = A / denom;
		}
		else if (instructions[pos] == 7)
		{
			int64_t denom = pow(2, combo(instructions[pos + 1], A, B, C));
			C = A / denom;
		}
		pos += posJump;
	}
	return output;
}

int main() {
	int64_t A = 63687530;
	int64_t B = 0;
	int64_t C = 0;
	vector<int> instructions = { 2,4,1,3,7,5,0,3,1,5,4,1,5,5,3,0 };
	vector<int> newVect;
	run(instructions, A, B, C, true);
	cout << endl;
	print(instructions);
	int64_t baseA = 216148338600000;
	//fanangle this number to get the last 9 digits to match
	A = baseA;
	int pos = 14;
	while (newVect != instructions)
	{
		A++;
		pos--;
		newVect = run(instructions, A, B, C, true);
		cout << endl;
	}
	cout << A << endl;
	
}