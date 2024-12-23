#include "elves.h"
#include <map>
#include <set>
#include <algorithm>
using namespace std;

bool checkClique(map<string, set<string>> links, vector<string> intersections)
{
	for (string t : intersections)
	{
		for (string s : intersections)
		{
			if (s != t && links[t].count(s) == 0)
			{
				return false;
			}
		}
	}
	return true;
}

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	map<string, set<string>> links;
	set<string> nodes;
	int64_t total = 0;
	int64_t total2 = 0;
	while (getline(FileName, lineN))
	{
		vector<string> split = splitString(lineN, { '-' });
		links[split[0]].insert(split[1]);
		links[split[1]].insert(split[0]);
		nodes.insert(split[0]);
		nodes.insert(split[1]);
	}

	set<set<string>> foundThrees;
	vector<string> maxInt;
	int maxIntersect = 0;
	for (string t : nodes)
	{
		for (string s : links[t])
		{
			vector<string> intersections;
			set_intersection(links[t].begin(), links[t].end(), links[s].begin(), links[s].end(), back_inserter(intersections));
			if (intersections.size() > maxIntersect)
			{
				bool clique = checkClique(links, intersections);
				if (clique)
				{
					maxIntersect = intersections.size();
					maxInt = intersections;
					maxInt.push_back(s);
					maxInt.push_back(t);
				}
			}
			for (string u : intersections)
			{
				set<string> found;
				found.insert(t); found.insert(s); found.insert(u);
				if (foundThrees.count(found) == 0)
				{
					foundThrees.insert(found);
					if(t[0] =='t' ||s[0]=='t'||u[0]=='t')
						total++;
					//cout << t << "-" << s << "-" << u << endl;
				}
			}
		}
	}
	cout << "P1: " << total << endl;
	set<string> part2(maxInt.begin(), maxInt.end());
	string answer;
	for (string p : part2)
	{
		answer+=p;
		answer += ',';
	}
	cout << answer.substr(0, answer.size() - 1) << endl;
}