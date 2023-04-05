//20. На  шахматном поле расположены N черных  и  одна  белая
//шашка.Требуется  написать  программу, которая  по  заданному
//расположению шашек определяет, какое  максимальное  колиsчество
//шашек может взять белая шашка за один ход.
//Ввод из файла INPUT.TXT.Задается 8 строк, каждая  содержит
//8 символов.Символом ‘0’ обозначается пустая клетка, символом
//‘1’ положение черной шашки и символом ‘2’ положение белой шашки.
//Вывод  в  файл  OUTPUT.TXT.Вывести  единственное  число –
//максимальное количество черных шашек, которых можно  взять  за
//один ход(11).

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool ReadInputFile(const string& input_file, string desk[8][8], int& position_by_x, int& position_by_y) {
	int white_figure_count = 0;

	ifstream fin(input_file);

	if (!fin.is_open()) {
		cerr << "Failed to open input file: " << input_file << endl;
		return false;
	}

	for (int y = 0; y < 8; y++) {
		string line;
		if (!getline(fin, line)) {
			cerr << "Failed to read line " << y << " from input file: " << input_file << endl;
			return false;
		}
		for (int x = 0; x < 8; x++) {
			desk[y][x] = line[x];

			if (line[x] == '2') {
				white_figure_count++;
				position_by_x = x;
				position_by_y = y;
			}
		}
	}
	fin.close();

	if (white_figure_count != 1) {
		cerr << "There ";
		cerr << (white_figure_count > 1 ? "are more than one white figure" : "is no white figure") << endl;
		return false;
	}

	return true;
}

int PrintDesk(string desk[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << desk[i][j];
		}
		cout << endl;
	}
	return 1;
}

int FindMaximum(const vector<int>& counts)
{
	int result = 0;

	for (int n : counts)
	{
		if (n > result)
			result = n;
	}
	cout << "Max count: " << result;
	return 1;
}

bool IsValidPosition(int x, int y)
{
	return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

bool IsValidMove(int from_x, int from_y, int to_x, int to_y, string desk[8][8])
{
	if (!IsValidPosition(from_x, from_y) || !IsValidPosition(to_x, to_y))
		return false;

	if (desk[to_y][to_x] != "1")
		return false;

	int dx = to_x - from_x;
	int dy = to_y - from_y;

	if (abs(dx) != abs(dy))
		return false;

	if (dx > 0 && desk[from_y][from_x] == "2")
		return false;

	if (dx < 0 && desk[from_y][from_x] == "1")
		return false;

	int step_x = (dx > 0) ? 1 : -1;
	int step_y = (dy > 0) ? 1 : -1;

	for (int x = from_x + step_x, y = from_y + step_y; x != to_x && y != to_y; x += step_x, y += step_y)
	{
		if (desk[y][x] != "0")
			return false;
	}

	return true;
}


int Move(int current_position_y, int current_position_x, string(&desk)[8][8], vector<int>& counts, int count)
{
	counts.push_back(count);
	int dx[4] = { -1, 1, 1, -1 };
	int dy[4] = { 1, 1, -1, -1 };

	for (int i = 0; i < 4; i++)
	{
		int new_x = current_position_x + dx[i];
		int new_y = current_position_y + dy[i];

		if (IsValidPosition(new_x, new_y))
		{
			if (desk[new_y][new_x] == "1" && IsValidPosition(new_x + dx[i], new_y + dy[i]) &&
				desk[new_y + dy[i]][new_x + dx[i]] != "1")
			{
				int new_count = count + 1;
				desk[new_y][new_x] = "0";
				Move(new_y + dy[i], new_x + dx[i], desk, counts, new_count);
				desk[new_y][new_x] = "1";
			}
		}
	}
	return 1;
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "Usage: program_name <input_file>" << endl;
		return 1;
	}
	const string input_file = argv[1];

	string desk[8][8];
	int position_by_x = -1;
	int position_by_y = -1;

	if (!ReadInputFile(input_file, desk, position_by_x, position_by_y)) {
		return 1;
	}

	vector<int> counts;
	Move(position_by_y, position_by_x, desk, counts, 0);
	FindMaximum(counts);

	return 0;
}