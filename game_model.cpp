#include "game_model.h"
#include <cstdlib>
#include <ctime>

// Конструктор
GameModel::GameModel(int size, int targetValue)
    : size(size), targetValue(targetValue), score(0), gameOver(false) {
    grid = new int*[size];
    for (int i = 0; i < size; ++i) {
        grid[i] = new int[size]();
    }
    spawnTile(); // Появление первой карточки
    spawnTile(); // Появление второй карточки
}

// Деструктор
GameModel::~GameModel() {
    for (int i = 0; i < size; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

void GameModel::setTile(int row, int col, int value) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        grid[row][col] = value;
    }
}

void GameModel::spawnTile() {
    if (gameOver) return;

    int x, y;
    do {
        x = rand() % size;
        y = rand() % size;
    } while (grid[x][y] != 0); // Ищем пустую клетку

    grid[x][y] = (rand() % 2 == 0) ? 2 : 4; // 50% вероятность появления 2 или 4
}

bool GameModel::isGameOver() {
    if (gameOver) return true;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j] == 0 ||
                (i < size - 1 && grid[i][j] == grid[i + 1][j]) ||
                (j < size - 1 && grid[i][j] == grid[i][j + 1])) {
                return false;
            }
        }
    }
    gameOver = true;
    return true;
}

int GameModel::getScore() const {
    return score;
}

int GameModel::getTile(int x, int y) const {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return grid[x][y];
    }
    return -1; // Возвращаем -1 для некорректных координат
}

int GameModel::getSize() const {
    return size;
}

