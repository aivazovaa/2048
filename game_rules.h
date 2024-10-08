#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game_model.h"
#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };

class GameRules {
public:
    void move(GameModel& model, Direction dir);
    bool canMove(const GameModel& model) const;
    void spawnTile(GameModel& model);

private:
    bool combineTiles(int& a, int& b);
    void slideAndCombine(std::vector<int>& line);
};

#endif // GAME_RULES_H

