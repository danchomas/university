#include "interface.h"
#include <locale.h>
#include <iostream>

Player::Player(const std::string& name, const std::string& position)
    : name(name), position(position) {}

void Player::kick(Ball& ball) {
    std::cout << name << " ударил по мячу " << ball.getBrand() << "!\n";
}

void Player::save() {
    std::cout << name << " спас ворота!\n";
}

std::string Player::getName() const {
    return name;
}

std::string Player::getPosition() const {
    return position;
}

Team::Team(const std::string& name, const std::vector<IPlayer*>& players)
    : name(name), players(players) {}

std::string Team::getName() const {
    return name;
}

const std::vector<IPlayer*>& Team::getPlayers() const {
    return players;
}

Stadium::Stadium(const std::string& name, int capacity)
    : name(name), capacity(capacity) {}

std::string Stadium::getName() const {
    return name;
}

int Stadium::getCapacity() const {
    return capacity;
}

Referee::Referee(const std::string& name)
    : name(name) {}

void Referee::startMatch() {
    std::cout << "Судья " << name << " дает свисток к началу матча!\n";
}

std::string Referee::getName() const {
    return name;
}

Ball::Ball(const std::string& brand, double weight)
    : brand(brand), weight(weight) {}

std::string Ball::getBrand() const {
    return brand;
}

double Ball::getWeight() const {
    return weight;
}
