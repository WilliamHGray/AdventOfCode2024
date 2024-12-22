#include "elves.h"
#include <map>
using namespace std;

map<string, string> instructions = { {"AA","A"}, {"A0","<A"}, {"A1","^<<A"}, {"A2","<^A"}, {"A3","^A"}, {"A4","^^<<A"}, {"A5","<^^A"}, {"A6","^^A"}, {"A7","^^^<<A"}, {"A8","<^^^A"}, {"A9","^^^A"},
									{"00","A"}, {"0A",">A"}, {"01","^<A"}, {"02","^A"}, {"03","^>A"}, {"04","^^<A"}, {"05","^^A"}, {"06","^^>A"}, {"07","^^^<A"}, {"08","^^^A"}, {"09","^^^>A"},
									{"11","A"}, {"1A",">>vA"}, {"10",">vA"}, {"12",">A"}, {"13",">>A"}, {"14","^A"}, {"15","^>A"}, {"16","^>>A"}, {"17","^^A"}, {"18","^^>A"}, {"19","^^>>A"},
									{"22","A"}, {"2A","v>A"}, {"20","vA"}, {"21","<A"}, {"23",">A"}, {"24","<^A"}, {"25","^A"}, {"26","^>A"}, {"27","<^^A"}, {"28","^^A"}, {"29","^^>A"},
									{"33","A"}, {"3A","vA"}, {"30","<vA"}, {"31","<<A"}, {"32","<A"}, {"34","<<^A"}, {"35","<^A"}, {"36","^A"}, {"37","<<^^A"}, {"38","<^^A"}, {"39","^^A"},
									{"44","A"}, {"4A",">>vvA"}, {"40",">vvA"}, {"41","vA"}, {"42","v>A"}, {"43","v>>A"}, {"45",">A"}, {"46",">>A"}, {"47","^A"}, {"48","^>A"}, {"49","^>>A"},
									{"55","A"}, {"5A","vv>A"}, {"50","vvA"}, {"51","<vA"}, {"52","vA"}, {"53","v>A"}, {"54","<A"}, {"56",">A"}, {"57","<^A"}, {"58","^A"}, {"59","^>A"},
									{"66","A"}, {"6A","vvA"}, {"60","<vvA"}, {"61","<<vA"}, {"62","<vA"}, {"63","vA"}, {"64","<<A"}, {"65","<A"}, {"67","<<^A"}, {"68","<^A"}, {"69","^A"},
									{"77","A"}, {"7A",">>vvvA"}, {"70",">vvvA"}, {"71","vvA"},{"72","vv>A"}, {"73","vv>>A"}, {"74","vA"}, {"75","v>A"}, {"76","v>>A"}, {"78",">A"}, {"79",">>A"},
									{"88","A"}, {"8A","vvv>A"}, {"80","vvvA"}, {"81","<vvA"},{"82","vvA"}, {"83","vv>A"}, {"84","<vA"}, {"85","vA"}, {"86","v>A"}, {"87","<A"}, {"89",">A"},
									{"99","A"}, {"9A","vvvA"}, {"90","<vvvA"}, {"91","<<vvA"},{"92","<vvA"}, {"93","vvA"}, {"94","<<vA"}, {"95","<vA"}, {"96","vA"}, {"97", "<<A"}, {"98","<A"},
									{"A<","v<<A"}, {"Av","<vA"}, {"A>","vA"},{"A^","<A"},
									{"<<","A"}, {"<A",">>^A"}, {"<v",">A"}, {"<>",">>A"},{"<^",">^A"},
									{"vv","A"}, {"vA","^>A"}, {"v<","<A"}, {"v>",">A"},{"v^","^A"},
									{">>","A"}, {">A","^A"}, {"><","<<A"}, {">v","<A"},{">^","<^A"},
									{"^^","A"}, {"^A",">A"}, {"^<","v<A"}, {"^v","vA"},{"^>","v>A"} };

int main() {
	ifstream FileName;
	FileName.open("aoc.txt");
	string lineN;
	vector<string> lines;
	int total = 0;
	int64_t total2 = 0;
	while (getline(FileName, lineN))
	{
		lines.push_back(lineN);
	}

	vector<string> run;
	int levels = 12;
	for (string line : lines)
	{
		string start = "";
		string instr = line;
		for (int j = 0; j < levels; j++)
		{
			string firstInstruction = "A";
			firstInstruction.append(1, instr[0]);
			start += instructions[firstInstruction];
			for (int i = 0; i < instr.size() - 1; i++)
			{
				start += instructions[instr.substr(i, 2)];
			}
			instr = start;
			start = "";
		}
		int num = stoi(line.substr(0, line.size() - 1));
		total += num * instr.size();
		run.push_back(instr);
	}
	cout << "P1: " << total << endl;
	
	map < string, int64_t> bigLengths;
	int numIt = 0;
	for (string line : run)
	{
		//cout << line << endl;
		int pos = 0;
		int newPos = line.find('A', pos);
		vector<string> single; 
		while (newPos != string::npos)
		{
			single.push_back(line.substr(pos, newPos - pos + 1));
			pos = newPos + 1;
			newPos = line.find('A', pos);
		}
		int64_t length = 0;
		int newLevels = 26 - levels;
		for (string it : single)
		{
			if (bigLengths.count(it) != 0)
			{
				length += bigLengths[it];
			}
			else
			{
				string start = "";
				string instr = it;
				for (int j = 0; j < newLevels; j++)
				{
					string firstInstruction = "A";
					firstInstruction.append(1, instr[0]);
					start += instructions[firstInstruction];
					for (int i = 0; i < instr.size() - 1; i++)
					{
						start += instructions[instr.substr(i, 2)];
					}
					instr = start;
					start = "";
				}
				bigLengths[it] = instr.size();
				length += bigLengths[it];
			}
		}
		int num = stoi(lines[numIt].substr(0, 3));
		cout << num << " * " << length << endl;
		numIt++;
		total2 += num * length;
	}
	cout << total2 << endl;
}
