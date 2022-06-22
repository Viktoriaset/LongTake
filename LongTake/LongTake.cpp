#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <utility>

const double PI = std::acos(-1);

std::vector<std::pair<int, int>> t(4);


struct answer {
	int len;
	std::string moves;
	std::vector<int> number;
};

void getPosition(int g, int v, int n, answer& ans) {
	ans.moves.push_back((char)(97 + v));
	ans.number.push_back(n - g);
	return;
}

bool ChekExistancePositioin(std::vector<std::string> table, int v, int g, bool chekMoving = false) {
	if (v >= table.size() || v < 0) {
		return false;
	}
	if (g >= table[v].size() || g < 0) {
		return false;
	}

	if (table[v][g] != '.' && chekMoving) {
		return false;
	}

	return true;
}

answer searchLongerTake(std::vector<std::string> table, int v, int g, answer sequence) {

	std::vector<answer> tempSequence;

	getPosition( v, g, table.size(), sequence);
	sequence.len++;

	for (int i = 0; i < t.size(); i++) {
		if (!ChekExistancePositioin(table, t[i].first + v, t[i].second + g)) {
			continue;
		}

		if (table[t[i].first + v][t[i].second + g] == 'O') {
			if (ChekExistancePositioin(table, t[i].first * 2 + v, t[i].second * 2 + g, true)) {
				table[t[i].first + v][t[i].second + g] = '.';
				tempSequence.push_back(searchLongerTake(table, t[i].first * 2 + v, t[i].second * 2 + g, sequence));
				table[t[i].first + v][t[i].second + g] = 'O';
			}
		}
	}

	for (int i = 0; i < tempSequence.size(); i++) {
		sequence = (sequence.number.size() > tempSequence[i].number.size()) ? sequence : tempSequence[i];
	}

	return sequence;
}

int main()
{
	std::ifstream inp("input.txt");
	std::ofstream out("output.txt");

	int n;
	inp >> n;

	std::vector<std::string> table(n);

	t[0] = { -1, 1 };
	t[1] = { 1, 1 };
	t[2] = { 1, -1 };
	t[3] = {-1, -1 };

	for (int i = 0; i < n; i++) {
		std::string temp;
		inp >> temp;
		table[i] = temp;
	}

	answer ans = { 0 };

	for (int i = 0; i < table.size(); i++) {
		for (int j = 0; j < table[i].size(); j++) {
			if (table[i][j] == 'X') {
				table[i][j] = '.';
				answer temp = { 0 };
				temp = searchLongerTake(table, i, j, temp);
				if (temp.len > ans.len) {
					ans = temp;
				}
				table[i][j] = 'X';
			}
		}
	}

	if (ans.len <= 1) {
		out << "Impossible";
		return 0;
	}

	for (int i = 0; i < ans.moves.size() -1; i++) {
		out << ans.moves[i] << ans.number[i] << '-';
	}

	out << ans.moves[ans.moves.size() - 1] << ans.number[ans.moves.size() - 1];

	return 0;
}
