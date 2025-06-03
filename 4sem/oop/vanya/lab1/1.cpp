#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

string toScientific(double num) {
    stringstream ss;
    ss << scientific << setprecision(2);
    ss << num;
    return ss.str();
}

int main() {
    string inputFilename = "1.txt";
    string outputFilename = "1-res.txt";

    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);

    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть входной файл: " << inputFilename << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть выходной файл: " << outputFilename << endl;
        return 1;
    }

    double number;
    while (inputFile >> number) {
        string scientificStr = toScientific(number);
        outputFile << scientificStr << "\n";
    }

    inputFile.close();
    outputFile.close();

    cout << "Преобразование завершено. Результат записан в " << outputFilename << endl;

    return 0;
}