#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <clocale>

void process_line(const std::string& input, std::string& output) {
    output.clear();
    bool previous_space = false;
    
    for (char c : input) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!previous_space) {
                output += ' ';
                previous_space = true;
            }
        }
        else {
            output += c;
            previous_space = false;
        }
    }
    
    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }
}

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл" << std::endl;
        return 1;
    }
    
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл" << std::endl;
        inputFile.close();
        return 1;
    }
    
    std::string line;
    std::string processed;
    size_t line_number = 0;
    
    while (std::getline(inputFile, line)) {
        line_number++;
        process_line(line, processed);
        outputFile << processed << '\n';
    }
    
    inputFile.close();
    outputFile.close();
    
    std::cout << "Файл успешно обработан. Обработано строк: " << line_number 
              << ". Результат в output.txt" << std::endl;
    return 0;
}