//2. Текстовый файл содержит последовательность  целых чисел,
//разделенных  произвольным  количеством других символов.Числа
//могут переходить со строки на строку.Требуется  найти  сумму
//чисел (6)

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    string input_filename = argv[1];

    ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        cerr << "Error: cannot open file " << input_filename << endl;
        return 1;
    }

    int sum = 0;
    string line;
    while (getline(input_file, line)) {
        istringstream iss(line);
        int num;
        while (iss >> num) {
            sum += num;
        }
    }

    input_file.close();

    cout << "Sum of numbers in file " << input_filename << " is " << sum << endl;

    return 0;
}
