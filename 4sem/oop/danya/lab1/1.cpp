#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <clocale>

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::ifstream inputFile("1.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл" << std::endl;
        return 1;
    }
    
    std::ofstream outputFile("1-res.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл" << std::endl;
        inputFile.close();
        return 1;
    }
    
    int matrixCount = 0;
    std::string line;
    
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;
        
        matrixCount++;
        std::istringstream iss(line);
        int n;
        
        if (!(iss >> n)) {
            std::cerr << "Ошибка в матрице " << matrixCount 
                      << ": некорректный порядок" << std::endl;
            continue;
        }
        
        if (n <= 0) {
            std::cerr << "Ошибка в матрице " << matrixCount 
                      << ": порядок должен быть > 0" << std::endl;
            continue;
        }
        
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
        bool error = false;
        
        for (int i = 0; i < n; ++i) {
            if (!std::getline(inputFile, line)) {
                std::cerr << "Ошибка в матрице " << matrixCount 
                          << ": недостаточно строк" << std::endl;
                error = true;
                break;
            }
            
            std::istringstream rowIss(line);
            int val, j = 0;
            
            while (rowIss >> val) {
                if (j >= n) {
                    std::cerr << "Ошибка в матрице " << matrixCount 
                              << ": избыток элементов в строке " << i + 1 << std::endl;
                    error = true;
                    break;
                }
                matrix[i][j++] = val;
            }
            
            if (j != n) {
                std::cerr << "Ошибка в матрице " << matrixCount 
                          << ": недостаточно элементов в строке " << i + 1 << std::endl;
                error = true;
            }
            
            if (error) break;
        }
        
        if (error) continue;
        
        outputFile << n << "\n";
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < n; ++i) {
                outputFile << matrix[i][j] << " ";
            }
            outputFile << "\n";
        }
        outputFile << "\n";
    }
    
    inputFile.close();
    outputFile.close();
    
    std::cout << "Обработано матриц: " << matrixCount << std::endl;
    return 0;
}