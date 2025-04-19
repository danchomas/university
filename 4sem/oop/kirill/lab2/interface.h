#pragma once
#ifndef INTERFACES_H
#define INTERFACES_H

#include <locale.h>
#include <iostream>
#include <string>
#include <vector>

class Ball;

class IPlayer {
public:
    virtual void kick(Ball& ball) = 0;
    virtual void save() = 0;
    virtual std::string getName() const = 0;
    virtual std::string getPosition() const = 0;
};

class ITeam {
public:
    virtual std::string getName() const = 0;
    virtual const std::vector<IPlayer*>& getPlayers() const = 0;
};

class IStadium {
public:
    virtual std::string getName() const = 0;
    virtual int getCapacity() const = 0;
};

class IReferee {
public:
    virtual void startMatch() = 0;
    virtual std::string getName() const = 0;
};

class IBall {
public:
    virtual std::string getBrand() const = 0;
    virtual double getWeight() const = 0;
};

class Player : public IPlayer {
public:
    Player(const std::string& name, const std::string& position);
    void kick(Ball& ball) override;
    void save() override;
    std::string getName() const override;
    std::string getPosition() const override;

private:
    std::string name;
    std::string position;
};

class Team : public ITeam {
public:
    Team(const std::string& name, const std::vector<IPlayer*>& players);
    std::string getName() const override;
    const std::vector<IPlayer*>& getPlayers() const override;

private:
    std::string name;
    std::vector<IPlayer*> players;
};

class Stadium : public IStadium {
public:
    Stadium(const std::string& name, int capacity);
    std::string getName() const override;
    int getCapacity() const override;

private:
    std::string name;
    int capacity;
};

class Referee : public IReferee {
public:
    Referee(const std::string& name);
    void startMatch() override;
    std::string getName() const override;

private:
    std::string name;
};

class Ball : public IBall {
public:
    Ball(const std::string& brand, double weight);
    std::string getBrand() const override;
    double getWeight() const override;

private:
    std::string brand;
    double weight;
};

#endif // INTERFACES_H
