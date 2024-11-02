#include "player.h"
#include <iostream>
#include <string>

Player *newPlayer(std::string name, int num_goals) {
    Player *player = new Player;
    player->name = name;
    player->num_goals = num_goals;
    return player;
}

Player *copyPlayer(const Player *p) {
    if (p == nullptr) {
        return nullptr;
    }
    return newPlayer(p->name, p->num_goals);
}

void printPlayer(const Player *p) {
    if (p == nullptr) {
        std::cout << "No player found!" << std::endl;
    } else {
        std::cout << "Player name: " << p->name << std::endl;
        std::cout << "Total goals: " << p->num_goals << std::endl;
    }
}

void deletePlayer(Player *p) {
    if (p != nullptr) {
        delete p;
    }
}