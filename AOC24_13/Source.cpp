#include "Elves.h"
using namespace std;

int64_t solve(vector<int64_t> A, vector<int64_t> B, vector<int64_t> C)
{
	int aCost = 3;
	int bCost = 1;
	int64_t x1 = C[0] * B[1] - B[0] * C[1];
	int64_t z2 = A[0] * B[1] - B[0] * A[1];
	int64_t y1 = A[0] * C[1] - C[0] * A[1];

	if (z2 != 0)
	{
		int64_t r1 = x1 % z2;
		int64_t r2 = y1 % z2;
		int64_t x = x1 / z2;
		int64_t y = y1 / z2;
		if (r1 == 0 && r2 == 0)
		{
			cout << "Press A " << x << " times and B " << y << " times" << endl;
			return x * aCost + y * bCost;
		}
	}

	return 0;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<vector<int64_t>> A,B,ans,ansP2;
	int64_t total = 0;
	int64_t total2 = 0;
	int64_t bigger = 10000000000000;


	int it = 0;
	while (getline(FileName, lineN))
	{
		int rem = it % 4;
		if (rem == 0)
		{
			int pos1 = lineN.find('+')+1;
			int pos2 = lineN.find('+', pos1)+1;
			int64_t A1 = stoll(lineN.substr(pos1, lineN.find(',', pos1) - pos1));
			int64_t A2 = stoll(lineN.substr(pos2));
			A.push_back({ A1,A2 });
		}
		else if (rem == 1)
		{
			int pos1 = lineN.find('+') + 1;
			int pos2 = lineN.find('+', pos1) + 1;
			int64_t B1 = stoll(lineN.substr(pos1, lineN.find(',', pos1) - pos1));
			int64_t B2 = stoll(lineN.substr(pos2));
			B.push_back({ B1,B2 });
		}
		if (rem == 2)
		{
			int pos1 = lineN.find('=') + 1;
			int pos2 = lineN.find('=', pos1) + 1;
			int64_t ans1 = stoll(lineN.substr(pos1, lineN.find(',', pos1) - pos1));
			int64_t ans2 = stoll(lineN.substr(pos2));
			ans.push_back({ ans1,ans2 });
			ansP2.push_back({ ans1 + bigger,ans2 + bigger });
		}
		it++;
	}

	for (int i = 0; i < A.size(); i++)
	{
		total += solve(A[i], B[i], ans[i]);
		total2 += solve(A[i], B[i], ansP2[i]);
	}
	cout << total << endl;
	cout << total2 << endl;
}