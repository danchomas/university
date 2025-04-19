#include <iostream>
#include "interface.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");

    Player player1("Лев Яшин", "вратарь");
    Player player2("Пеле", "нападающий");
    Player player3("Игорь Акинфеев", "вратарь");
    Player player4("Артем Дзюба", "нападающий");

    Team team1("Сборная Бразилии", { &player1, &player2 });
    Team team2("Сборная России", { &player3, &player4 });

    Stadium stadium("Лужники", 81000);
    Referee referee("Пьерлуиджи Коллина");
    Ball ball("Nike", 0.7);

    std::cout << "Матч начинается на стадионе " << stadium.getName() << "!\n";
    std::cout << "Судья: " << referee.getName() << "\n";
    std::cout << "Команды: " << team1.getName() << " vs " << team2.getName() << "\n";

    referee.startMatch();
    player2.kick(ball);
    player1.save();

    std::cout << "Матч завершен!\n";

    return 0;
}
