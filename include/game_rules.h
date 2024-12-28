#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game_model.h"
#include <vector>

enum Direction {
    NONE = -1,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    MENU
};


class GameRules {
public:
    void move(GameModel& model, Direction dir);
    bool canMove(const GameModel& model) const;
    void spawnTile(GameModel& model);
    void slideAndCombine(std::vector<int>& line, GameModel& model);  // Передаем model как аргумент
    bool isGameOver(const GameModel& model);

private:
    bool gameOver;
    bool combineTiles(int& a, int& b, GameModel& model);  // Передаем model как аргумент
    bool slideTiles(std::vector<int>& line);
};
#endif // GAME_RULES_H

