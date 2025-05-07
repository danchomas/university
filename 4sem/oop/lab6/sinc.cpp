#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

class RunningText {
private:
    std::string text;
    bool running;

public:
    RunningText() : running(true) {
        srand(time(nullptr));
    }

    void stop() {
        running = false;
    }

    void generateRunningString() {
        char c = 'a' + rand() % 26;
        text += c;
        if (text.length() > 20) {
            text = text.substr(0, 20);
            stop();
        }
    }

    void modifyPunctuation() {
        const std::string punctuation = ".,!?;:";
        if (!text.empty() && text.length() <= 20) {
            if (rand() % 2 == 0) {
                size_t pos = rand() % (text.length() + 1);
                char p = punctuation[rand() % punctuation.length()];
                text.insert(pos, 1, p);
                if (text.length() > 20) {
                    text = text.substr(0, 20);
                    stop();
                }
            } else {
                size_t found = text.find_first_of(punctuation);
                if (found != std::string::npos) {
                    text.erase(found, 1);
                }
            }
        }
    }

    void display() {
        std::cout << "\rТекущая строка: " << text << " \tДлина: " << text.length();
        std::cout.flush();
    }

    void runSync() {
        while (running) {
            generateRunningString();
            modifyPunctuation();
            display();
            usleep(200000);

            if (text.length() >= 20) {
                stop();
            }
        }
        std::cout << std::endl;
    }

    std::string getText() {
        return text;
    }
};

int main() {
    RunningText rt;

    rt.runSync();

    std::cout << "Финальная строка: " << rt.getText() << std::endl;
    return 0;
}