#include "game_rules.h"
#include <algorithm>

void GameRules::move(GameModel& model, Direction dir) {
    int size = model.getSize();
    std::vector<int> line(size);

    if (dir == LEFT || dir == RIGHT) {
        // Перемещение по горизонтали
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                line[j] = model.getTile(i, j);
            }
            if (dir == RIGHT) {
                std::reverse(line.begin(), line.end());
            }
            slideAndCombine(line);
            if (dir == RIGHT) {
                std::reverse(line.begin(), line.end());
            }
            for (int j = 0; j < size; ++j) {
                model.setTile(i, j, line[j]);
            }
        }
    } else {
        // Перемещение по вертикали
        for (int j = 0; j < size; ++j) {
            for (int i = 0; i < size; ++i) {
                line[i] = model.getTile(i, j);
            }
            if (dir == DOWN) {
                std::reverse(line.begin(), line.end());
            }
            slideAndCombine(line);
            if (dir == DOWN) {
                std::reverse(line.begin(), line.end());
            }
            for (int i = 0; i < size; ++i) {
                model.setTile(i, j, line[i]);
            }
        }
    }
}

bool GameRules::canMove(const GameModel& model) const {
    int size = model.getSize();
    // Проверка возможности объединения или перемещения
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int currentTile = model.getTile(i, j);
            if (currentTile == 0) return true;  // Есть пустое место
            if (i < size - 1 && model.getTile(i + 1, j) == currentTile) return true;  // Можно объединить вниз
            if (j < size - 1 && model.getTile(i, j + 1) == currentTile) return true;  // Можно объединить вправо
        }
    }
    return false;
}

void GameRules::spawnTile(GameModel& model) {
    std::vector<std::pair<int, int>> emptyTiles;
    int size = model.getSize();

    // Поиск всех пустых ячеек
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (model.getTile(i, j) == 0) {
                emptyTiles.emplace_back(i, j);
            }
        }
    }

    // Если есть пустые ячейки, добавляем новую плитку
    if (!emptyTiles.empty()) {
        int randomIndex = rand() % emptyTiles.size();
        int tileValue = (rand() % 2 == 0) ? 2 : 4; // 50% шанс на 2 или 4
        model.setTile(emptyTiles[randomIndex].first, emptyTiles[randomIndex].second, tileValue);
    }
}

bool GameRules::combineTiles(int& a, int& b) {
    if (a == b && a != 0) {
        a *= 2;
        b = 0;
        return true;
    }
    return false;
}

// Метод для перемещения плиток в ряду/колонке и их объединения
void GameRules::slideAndCombine(std::vector<int>& line) {
    std::vector<int>::size_type size = line.size();
    int lastNonZero = -1;

    for (std::vector<int>::size_type i = 0; i < size; ++i) {
        if (line[i] != 0) {
            if (lastNonZero != -1 && combineTiles(line[lastNonZero], line[i])) {
                lastNonZero = -1;
            } else {
                if (lastNonZero != -1 && lastNonZero + 1 != i) {
                    std::swap(line[lastNonZero + 1], line[i]);
                }
                lastNonZero++;
            }
        }
    }
}

