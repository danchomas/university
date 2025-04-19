#include <windows.h>
#include <string>
#include <iostream>
#include <ctime>

// Объявления глобальных переменных
CRITICAL_SECTION cs;
bool sync = true;
std::string buffer = ">>>";

// Прототипы функций
char getRandomChar();
char getRandomPunct();
DWORD WINAPI RunningLine(LPVOID);
DWORD WINAPI ModifyPunctuation(LPVOID);
void RunMode(const char* modeName, bool syncMode);

// Реализация функций
char getRandomChar() {
    return 'A' + rand() % 26;
}

char getRandomPunct() {
    const char puncts[] = { '.', ',', '?', '!', ':', ';', '-' };
    return puncts[rand() % (sizeof(puncts) / sizeof(char))];
}

DWORD WINAPI RunningLine(LPVOID) {
    for (int i = 0; i < 12; ++i) {
        if (sync) {
            EnterCriticalSection(&cs);
        }
        
        if (!buffer.empty()) {
            buffer.erase(0, 1);
        }
        buffer += getRandomChar();
        std::cout << "Бегущая строка: " << buffer << std::endl;
        
        if (sync) {
            LeaveCriticalSection(&cs);
        }
        Sleep(100);
    }
    return 0;
}

DWORD WINAPI ModifyPunctuation(LPVOID) {
    for (int i = 0; i < 12; ++i) {
        if (sync) {
            EnterCriticalSection(&cs);
        }
        
        if (rand() % 2 == 0 && !buffer.empty()) {
            int pos = rand() % (buffer.length() + 1);
            buffer.insert(pos, 1, getRandomPunct());
            std::cout << "Добавление знака препинания: " << buffer << std::endl;
        }
        else {
            for (size_t i = 0; i < buffer.size(); ++i) {
                if (ispunct(buffer[i])) {
                    buffer.erase(i, 1);
                    std::cout << "Удаление знака препинания: " << buffer << std::endl;
                    break;
                }
            }
        }
        
        if (sync) {
            LeaveCriticalSection(&cs);
        }
        Sleep(120);
    }
    return 0;
}

void RunMode(const char* modeName, bool syncMode) {
    sync = syncMode;
    buffer = ">>>";
    std::cout << "\n" << modeName << std::endl;
    std::cout << "Начальная строка: " << buffer << std::endl;
    
    HANDLE t1 = CreateThread(NULL, 0, RunningLine, NULL, 0, NULL);
    HANDLE t2 = CreateThread(NULL, 0, ModifyPunctuation, NULL, 0, NULL);
    
    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);
    
    CloseHandle(t1);
    CloseHandle(t2);
}

int main() {
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned>(time(0)));
    
    InitializeCriticalSection(&cs);
    
    RunMode("Синхронный режим", true);
    RunMode("Асинхронный режим", false);
    
    DeleteCriticalSection(&cs);
    std::cout << "\nРабота завершена." << std::endl;
    
    return 0;
}