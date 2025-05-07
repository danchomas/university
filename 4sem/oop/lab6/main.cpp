#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstdlib>
#include <string>

class NumHandler {
private:
    std::string line;
    std::mutex& mtx;
public:
    NumHandler(std::mutex& m);
    void addDigit(bool sync);
    void removeDigit(bool sync);
    void printInitial(const std::string& label);
};

class NumHandlerThread {
public:
    void runAdd(NumHandler& handler, bool sync);
    void runRemove(NumHandler& handler, bool sync);
};

NumHandler::NumHandler(std::mutex& m) : mtx(m), line("123456789") {}

void NumHandler::addDigit(bool sync) {
    if (sync) {
        mtx.lock();
    }
    char digit = '0' + rand() % 10;
    line += digit;
    std::cout << "Добавление числа: " << line << std::endl;
    if (sync) {
        mtx.unlock();
    }
}

void NumHandler::removeDigit(bool sync) {
    if (sync) {
        mtx.lock();
    }
    if (!line.empty()) {
        int pos = rand() % line.size();
        line.erase(pos, 1);
        std::cout << "Удаление числа: " << line << std::endl;
    }
    if (sync) {
        mtx.unlock();
    }
}

void NumHandler::printInitial(const std::string& label) {
    std::cout << label << std::endl;
    std::cout << "Начальная строка: " << line << std::endl;
}

void NumHandlerThread::runAdd(NumHandler& handler, bool sync) {
    for (int i = 0; i < 6; ++i) {
        handler.addDigit(sync);
    }
}

void NumHandlerThread::runRemove(NumHandler& handler, bool sync) {
    for (int i = 0; i < 6; ++i) {
        handler.removeDigit(sync);
    }
}

int main() {
    // Установка локали для поддержки кириллицы
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    
    srand(static_cast<unsigned>(time(nullptr)));

    std::mutex mtx;
    NumHandler syncHandler(mtx);
    NumHandlerThread handlerThread;

    syncHandler.printInitial("Синхронный режим");
    std::thread t1(&NumHandlerThread::runAdd, &handlerThread,
        std::ref(syncHandler), true);
    std::thread t2(&NumHandlerThread::runRemove, &handlerThread,
        std::ref(syncHandler), true);
    t1.join();
    t2.join();

    std::cout << "\n";

    NumHandler asyncHandler(mtx);
    asyncHandler.printInitial("Асинхронный режим");
    std::thread t3(&NumHandlerThread::runAdd, &handlerThread,
        std::ref(asyncHandler), false);
    std::thread t4(&NumHandlerThread::runRemove, &handlerThread,
        std::ref(asyncHandler), false);
    t3.join();
    t4.join();

    std::cout << "\nЗавершено." << std::endl;
    return 0;
}